
// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

#include "ClientChunkRequest.h"
#include <algorithm>

std::queue<std::shared_ptr<ClientChunkRequest::Chunk>> ClientChunkRequest::freeChunks;
std::queue<ByteBuffer*> ClientChunkRequest::freeBuffers;
std::mutex ClientChunkRequest::freeChunksMutex;
std::mutex ClientChunkRequest::freeBuffersMutex;

ClientChunkRequest::ClientChunkRequest() {}
ClientChunkRequest::~ClientChunkRequest() {}

std::shared_ptr<ClientChunkRequest::Chunk> ClientChunkRequest::getChunk() {
    // Java: Chunk var1 = freeChunks.poll(); if (var1 == null) var1 = new Chunk(); return var1;
    std::lock_guard<std::mutex> lock(freeChunksMutex);
    if (!freeChunks.empty()) {
        auto chunk = freeChunks.front();
        freeChunks.pop();
        return chunk;
    }
    return std::make_shared<Chunk>();
}

void ClientChunkRequest::releaseChunk(std::shared_ptr<Chunk> chunk) {
    // Java: this.releaseBuffer(var1); freeChunks.add(var1);
    releaseBuffer(chunk);
    std::lock_guard<std::mutex> lock(freeChunksMutex);
    freeChunks.push(chunk);
}

void ClientChunkRequest::getByteBuffer(std::shared_ptr<Chunk> chunk) {
    // Java: var1.bb = freeBuffers.poll(); if (var1.bb == null) var1.bb = ByteBuffer.allocate(16384); else var1.bb.clear();
    std::lock_guard<std::mutex> lock(freeBuffersMutex);
    if (!freeBuffers.empty()) {
        chunk->bb = freeBuffers.front();
        freeBuffers.pop();
        if (chunk->bb) chunk->bb->clear();
    } else {
        // Allocate new ByteBuffer(16384)
        chunk->bb = new ByteBuffer(16384);
    }
}

void ClientChunkRequest::releaseBuffer(std::shared_ptr<Chunk> chunk) {
    // Java: if (var1.bb != null) { freeBuffers.add(var1.bb); var1.bb = null; }
    if (chunk->bb != nullptr) {
        std::lock_guard<std::mutex> lock(freeBuffersMutex);
        freeBuffers.push(chunk->bb);
        chunk->bb = nullptr;
    }
}

void ClientChunkRequest::releaseBuffers() {
    // Java: for (int i = 0; i < this.chunks.size(); i++) { this.chunks.get(i).bb = null; }
    for (auto& chunk : chunks) {
        chunk->bb = nullptr;
    }
}

void ClientChunkRequest::unpack(ByteBuffer* buffer, UdpConnection* conn) {
    // Java: release all buffers, add all chunks to freeChunks, clear chunks, then read count and fill new chunks
    for (auto& chunk : chunks) {
        releaseBuffer(chunk);
    }
    {
        std::lock_guard<std::mutex> lock(freeChunksMutex);
        while (!chunks.empty()) {
            freeChunks.push(chunks.back());
            chunks.pop_back();
        }
    }
    int count = buffer->getInt();
    for (int i = 0; i < count; ++i) {
        auto chunk = getChunk();
        chunk->requestNumber = buffer->getInt();
        chunk->wx = buffer->getInt();
        chunk->wy = buffer->getInt();
        chunk->crc = buffer->getLong();
        chunks.push_back(chunk);
    }
    largeArea = false;
}

void ClientChunkRequest::unpackLargeArea(ByteBuffer* buffer, UdpConnection* conn) {
    // Java: release all buffers, add all chunks to freeChunks, clear chunks, then read min/max and fill new chunks
    for (auto& chunk : chunks) {
        releaseBuffer(chunk);
    }
    {
        std::lock_guard<std::mutex> lock(freeChunksMutex);
        while (!chunks.empty()) {
            freeChunks.push(chunks.back());
            chunks.pop_back();
        }
    }
    minX = buffer->getInt();
    minY = buffer->getInt();
    maxX = buffer->getInt();
    maxY = buffer->getInt();
    for (int x = minX; x < maxX; ++x) {
        for (int y = minY; y < maxY; ++y) {
            auto chunk = getChunk();
            chunk->requestNumber = buffer->getInt();
            chunk->wx = x;
            chunk->wy = y;
            chunk->crc = buffer->getLong();
            releaseBuffer(chunk);
            chunks.push_back(chunk);
        }
    }
    largeArea = true;
}

ClientChunkRequest::Chunk::Chunk() {}
ClientChunkRequest::Chunk::~Chunk() {}
