#pragma once

// Ported from Java: ClientChunkRequest and ClientChunkRequest.Chunk

#include <vector>
#include <queue>
#include <memory>
#include <cstdint>
#include <mutex>
#include <atomic>
#include <string>

namespace zombie {
namespace network {

class ByteBuffer; // Forward declaration for buffer type
class UdpConnection; // Forward declaration

class ClientChunkRequest {
public:
    ClientChunkRequest();
    ~ClientChunkRequest();

    // Fields
    std::vector<std::shared_ptr<class Chunk>> chunks;
    bool largeArea = false;
    int minX = 0, maxX = 0, minY = 0, maxY = 0;

    // Methods
    std::shared_ptr<class Chunk> getChunk();
    void releaseChunk(std::shared_ptr<class Chunk> chunk);
    void getByteBuffer(std::shared_ptr<class Chunk> chunk);
    void releaseBuffer(std::shared_ptr<class Chunk> chunk);
    void releaseBuffers();
    void unpack(ByteBuffer* buffer, UdpConnection* conn);
    void unpackLargeArea(ByteBuffer* buffer, UdpConnection* conn);

    // Static fields
    static std::queue<std::shared_ptr<class Chunk>> freeChunks;
    static std::queue<ByteBuffer*> freeBuffers;
    static std::mutex freeChunksMutex;
    static std::mutex freeBuffersMutex;

    class Chunk {
    public:
        Chunk();
        ~Chunk();

        // Fields
        int requestNumber = 0;
        int wx = 0;
        int wy = 0;
        int64_t crc = 0;
        ByteBuffer* bb = nullptr;
    };
};

} // namespace network
} // namespace zombie
