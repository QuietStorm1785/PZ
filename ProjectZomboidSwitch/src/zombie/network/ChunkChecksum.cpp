
// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

#include "ChunkChecksum.h"
#include <cstring>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "../zlib/zlib.h"

std::unordered_map<int, long> ChunkChecksum::checksumCache;
std::mutex ChunkChecksum::cacheMutex;
std::string ChunkChecksum::stringBuilder;
char ChunkChecksum::bytes[1024];

ChunkChecksum::ChunkChecksum() {}
ChunkChecksum::~ChunkChecksum() {}

void ChunkChecksum::noise(const std::string& msg) {
    // TODO: Only print if debug
    // std::cout << "ChunkChecksum: " << msg << std::endl;
}

long ChunkChecksum::getChecksum(int x, int y) {
    // Ported from Java
    // MPStatistic.getInstance().ChunkChecksum.Start();
    long crc = 0;
    std::lock_guard<std::mutex> lock(cacheMutex);
    int key = x + y * 30 * 1000;
    auto it = checksumCache.find(key);
    if (it != checksumCache.end()) {
        noise(std::to_string(x) + "," + std::to_string(y) + " found in cache crc=" + std::to_string(it->second));
        crc = it->second;
    } else {
           stringBuilder.clear();
           // Use actual game mode cache dir and save world if available
           // Example: std::string gameModeCacheDir = ZomboidFileSystem::instance().getGameModeCacheDir();
           // Example: std::string gameSaveWorld = Core::GameSaveWorld;
            std::string gameModeCacheDir = ZomboidFileSystem::getGameModeCacheDir();
            std::string gameSaveWorld = Core::GameSaveWorld;
           stringBuilder += gameModeCacheDir;
           stringBuilder += "/";
           stringBuilder += gameSaveWorld;
           stringBuilder += "/map_";
           stringBuilder += std::to_string(x);
           stringBuilder += "_";
           stringBuilder += std::to_string(y);
           stringBuilder += ".bin";
           crc = createChecksum(stringBuilder);
           checksumCache[key] = crc;
           noise(std::to_string(x) + "," + std::to_string(y) + " read from disk crc=" + std::to_string(crc));
    }
    // MPStatistic.getInstance().ChunkChecksum.End();
    return crc;
}


long ChunkChecksum::getChecksumIfExists(int x, int y) {
    long crc = 0;
    std::lock_guard<std::mutex> lock(cacheMutex);
    int key = x + y * 30 * 1000;
    auto it = checksumCache.find(key);
    if (it != checksumCache.end()) {
        crc = it->second;
    }
    return crc;
}


void ChunkChecksum::setChecksum(int x, int y, long crc) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    int key = x + y * 30 * 1000;
    checksumCache[key] = crc;
    noise(std::to_string(x) + "," + std::to_string(y) + " set crc=" + std::to_string(crc));
}


long ChunkChecksum::createChecksum(const std::string& path) {
    // Ported from Java: use std::filesystem and std::ifstream
    namespace fs = std::filesystem;
    fs::path filePath(path);
    if (!fs::exists(filePath)) {
        return 0;
    }
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return 0;
    }
    uLong crc = crc32(0L, Z_NULL, 0); // Initial value
    while (file) {
        file.read(bytes, sizeof(bytes));
        std::streamsize n = file.gcount();
        if (n > 0)
            crc = crc32(crc, reinterpret_cast<const Bytef*>(bytes), static_cast<uInt>(n));
    }
    file.close();
    return static_cast<long>(crc);
}

// NAMESPACE WRAP END
} // namespace network
} // namespace zombie
