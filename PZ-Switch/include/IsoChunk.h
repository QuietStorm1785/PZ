#pragma once
#include <vector>
#include <memory>
#include <cstdint>
#include <ctime>
#include <functional>

class IsoGridSquare;
class IsoCell;

/**
 * IsoChunk - A chunk of tiles (32x32 grid) for efficient world management
 * Chunks can be loaded/unloaded dynamically with Z-level support
 * 
 * Layout:
 * - 32x32 grid of IsoGridSquare tiles
 * - Each square can have multiple Z-levels
 * - Coordinates relative to chunk (0-31)
 * - World coordinates = chunk * 32 + local
 */
class IsoChunk {
public:
    static const int CHUNK_SIZE = 32;
    static constexpr float CHUNK_SIZE_F = 32.0f;

    IsoChunk(IsoCell* cell, int chunkX, int chunkY, int z);
    ~IsoChunk();

    // Access
    IsoGridSquare* getGridSquare(int x, int y);
    const IsoGridSquare* getGridSquare(int x, int y) const;

    // Chunk coordinates
    int getChunkX() const { return chunkX; }
    int getChunkY() const { return chunkY; }
    int getZ() const { return z; }
    
    // Get world coordinates from chunk-local coordinates
    int getWorldX(int localX) const { return chunkX * CHUNK_SIZE + localX; }
    int getWorldY(int localY) const { return chunkY * CHUNK_SIZE + localY; }

    // Loading state
    bool isLoaded() const { return loaded; }
    void setLoaded(bool l) { loaded = l; }
    void load();
    void unload();
    
    // Load time tracking
    float getLoadTime() const { return loadTime; }
    int64_t getLastAccessTime() const { return lastAccessTime; }
    void touchAccess() { lastAccessTime = std::time(nullptr); }

    // Rendering (forward declarations)
    class ChunkRenderer;
    friend class ChunkRenderer;

    // Memory tracking
    size_t getMemoryUsage() const;
    
    // For iteration (used by rendering)
    void forEachTile(std::function<void(IsoGridSquare*)> callback);

    // Update all squares in chunk
    void update();

    // Statistics
    int getTileCount() const { return CHUNK_SIZE * CHUNK_SIZE; }

private:
    IsoCell* cell;
    int chunkX, chunkY, z;
    bool loaded;
    float loadTime;
    int64_t lastAccessTime;

    // 32x32 grid of squares (owned by chunk)
    std::unique_ptr<IsoGridSquare> squares[CHUNK_SIZE][CHUNK_SIZE];

    void createSquares();
    void linkNeighbors();
    void linkNeighboringChunks();
};
