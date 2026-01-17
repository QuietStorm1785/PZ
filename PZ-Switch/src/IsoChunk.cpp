#include "IsoChunk.h"
#include "IsoGridSquare.h"
#include "IsoCell.h"
#include <ctime>
#include <iostream>
#include <functional>

IsoChunk::IsoChunk(IsoCell* cell, int chunkX, int chunkY, int z)
    : cell(cell)
    , chunkX(chunkX)
    , chunkY(chunkY)
    , z(z)
    , loaded(false)
    , loadTime(0.0f)
    , lastAccessTime(0) {
    
    // unique_ptr array is already initialized to nullptr
}

IsoChunk::~IsoChunk() {
    unload();
}

void IsoChunk::load() {
    if (loaded) return;
    
    auto startTime = std::time(nullptr);
    
    createSquares();
    linkNeighbors();
    linkNeighboringChunks();
    
    loadTime = std::difftime(std::time(nullptr), startTime);
    lastAccessTime = std::time(nullptr);
    loaded = true;
}

void IsoChunk::unload() {
    if (!loaded) return;
    
    // Reset all unique_ptrs (automatic deletion)
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            squares[x][y].reset();
        }
    }
    
    loaded = false;
}

IsoGridSquare* IsoChunk::getGridSquare(int x, int y) {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_SIZE) {
        return nullptr;
    }
    return squares[x][y].get();  // Get raw pointer from unique_ptr
}

const IsoGridSquare* IsoChunk::getGridSquare(int x, int y) const {
    if (x < 0 || x >= CHUNK_SIZE || y < 0 || y >= CHUNK_SIZE) {
        return nullptr;
    }
    return squares[x][y].get();  // Get raw pointer from unique_ptr
}

void IsoChunk::update() {
    if (!loaded) return;
    
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            if (squares[x][y]) {
                squares[x][y]->update();
            }
        }
    }
}

void IsoChunk::createSquares() {
    // Create all squares in this chunk with unique_ptr
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            int worldX = chunkX * CHUNK_SIZE + x;
            int worldY = chunkY * CHUNK_SIZE + y;
            squares[x][y] = std::make_unique<IsoGridSquare>(cell, worldX, worldY, z);
        }
    }
}

void IsoChunk::linkNeighbors() {
    // Link neighboring squares within this chunk
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            IsoGridSquare* sq = squares[x][y].get();
            if (!sq) continue;
            
            // Link 8-way neighbors (get raw pointers from unique_ptr)
            if (y > 0) sq->setN(squares[x][y-1].get());
            if (y < CHUNK_SIZE-1) sq->setS(squares[x][y+1].get());
            if (x < CHUNK_SIZE-1) sq->setE(squares[x+1][y].get());
            if (x > 0) sq->setW(squares[x-1][y].get());
            
            if (x < CHUNK_SIZE-1 && y > 0) sq->setNE(squares[x+1][y-1].get());
            if (x > 0 && y > 0) sq->setNW(squares[x-1][y-1].get());
            if (x < CHUNK_SIZE-1 && y < CHUNK_SIZE-1) sq->setSE(squares[x+1][y+1].get());
            if (x > 0 && y < CHUNK_SIZE-1) sq->setSW(squares[x-1][y+1].get());
        }
    }

    // Link neighbors across chunk boundaries if adjacent chunks are loaded
    auto linkAcross = [&](int localX, int localY, int nChunkX, int nChunkY, int nLocalX, int nLocalY,
                          void (IsoGridSquare::*setter)(IsoGridSquare*),
                          void (IsoGridSquare::*revSetter)(IsoGridSquare*)) {
        IsoChunk* neighborChunk = cell ? cell->getChunk(nChunkX, nChunkY, z) : nullptr;
        if (!neighborChunk || !neighborChunk->isLoaded()) return;

        IsoGridSquare* a = getGridSquare(localX, localY);
        IsoGridSquare* b = neighborChunk->getGridSquare(nLocalX, nLocalY);
        if (!a || !b) return;

        (a->*setter)(b);
        (b->*revSetter)(a);
    };

    int last = CHUNK_SIZE - 1;

    // East/West edges
    for (int y = 0; y < CHUNK_SIZE; ++y) {
        linkAcross(last, y, chunkX + 1, chunkY, 0, y, &IsoGridSquare::setE, &IsoGridSquare::setW);
        linkAcross(0, y, chunkX - 1, chunkY, last, y, &IsoGridSquare::setW, &IsoGridSquare::setE);
    }

    // North/South edges
    for (int x = 0; x < CHUNK_SIZE; ++x) {
        linkAcross(x, 0, chunkX, chunkY - 1, x, last, &IsoGridSquare::setN, &IsoGridSquare::setS);
        linkAcross(x, last, chunkX, chunkY + 1, x, 0, &IsoGridSquare::setS, &IsoGridSquare::setN);
    }
    
    // Diagonals
    linkAcross(last, 0, chunkX + 1, chunkY - 1, 0, last, &IsoGridSquare::setNE, &IsoGridSquare::setSW);
    linkAcross(0, 0, chunkX - 1, chunkY - 1, last, last, &IsoGridSquare::setNW, &IsoGridSquare::setSE);
    linkAcross(last, last, chunkX + 1, chunkY + 1, 0, 0, &IsoGridSquare::setSE, &IsoGridSquare::setNW);
    linkAcross(0, last, chunkX - 1, chunkY + 1, last, 0, &IsoGridSquare::setSW, &IsoGridSquare::setNE);
}

void IsoChunk::linkNeighboringChunks() {
    // Link diagonal neighbors across chunk boundaries
    // This is called after all adjacent chunks are guaranteed to exist
    int last = CHUNK_SIZE - 1;
    
    auto linkDiagonal = [&](int localX, int localY, int nChunkX, int nChunkY, int nLocalX, int nLocalY,
                            void (IsoGridSquare::*setter)(IsoGridSquare*),
                            void (IsoGridSquare::*revSetter)(IsoGridSquare*)) {
        IsoChunk* neighborChunk = cell ? cell->getChunk(nChunkX, nChunkY, z) : nullptr;
        if (!neighborChunk || !neighborChunk->isLoaded()) return;

        IsoGridSquare* a = getGridSquare(localX, localY);
        IsoGridSquare* b = neighborChunk->getGridSquare(nLocalX, nLocalY);
        if (!a || !b) return;

        (a->*setter)(b);
        (b->*revSetter)(a);
    };
    
    // Corner diagonals
    linkDiagonal(last, last, chunkX + 1, chunkY + 1, 0, 0, &IsoGridSquare::setSE, &IsoGridSquare::setNW);
    linkDiagonal(0, last, chunkX - 1, chunkY + 1, last, 0, &IsoGridSquare::setSW, &IsoGridSquare::setNE);
    linkDiagonal(last, 0, chunkX + 1, chunkY - 1, 0, last, &IsoGridSquare::setNE, &IsoGridSquare::setSW);
    linkDiagonal(0, 0, chunkX - 1, chunkY - 1, last, last, &IsoGridSquare::setNW, &IsoGridSquare::setSE);
}

void IsoChunk::forEachTile(std::function<void(IsoGridSquare*)> callback) {
    if (!callback) return;
    
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            IsoGridSquare* sq = getGridSquare(x, y);
            if (sq) callback(sq);
        }
    }
}

size_t IsoChunk::getMemoryUsage() const {
    // Base chunk structure
    size_t usage = sizeof(IsoChunk);
    
    // Grid squares (1024 tiles per chunk)
    usage += CHUNK_SIZE * CHUNK_SIZE * sizeof(IsoGridSquare);
    
    // Estimate object storage per tile
    static constexpr int AVG_OBJECTS_PER_TILE = 2;
    usage += CHUNK_SIZE * CHUNK_SIZE * AVG_OBJECTS_PER_TILE * sizeof(void*);
    
    return usage;
}
