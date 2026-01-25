#pragma once

// Ported from Java: ChunkChecksum

#include <string>
#include <mutex>
#include <unordered_map>
#include <zlib.h>

namespace zombie {
namespace network {

class ChunkChecksum {
public:
    ChunkChecksum();
    ~ChunkChecksum();

    // Static methods
    static long getChecksum(int x, int y);
    static long getChecksumIfExists(int x, int y);
    static void setChecksum(int x, int y, long crc);
    static long createChecksum(const std::string& path);


private:
    // Static fields
    static std::unordered_map<int, long> checksumCache;
    static std::mutex cacheMutex;
    static std::string stringBuilder;

    // CRC32 and buffer
    // Use zlib for CRC32 calculation
    static unsigned long crc32Value;
    static char bytes[1024];

    // CRC32 calculation using zlib
    static unsigned long calcCRC32(const char* data, size_t len) {
        // zlib crc32: initial value 0, update with data
        // Requires: #include <zlib.h>
        // Link with -lz if needed
        extern "C" unsigned long crc32(unsigned long crc, const unsigned char* buf, unsigned int len);
        return crc32(0L, reinterpret_cast<const unsigned char*>(data), static_cast<unsigned int>(len));
    }

    static void noise(const std::string& msg) {
        // Ported from Java: print debug info if needed
        // (In Java, this would check a debug flag; here we just print)
        #ifdef CHUNKCHECKSUM_DEBUG
        std::cerr << "[ChunkChecksum] " << msg << std::endl;
        #endif
    }
};

} // namespace network
} // namespace zombie
