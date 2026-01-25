// ShortenedIDMap.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <unordered_map>
#include <string>
#include <cstdint>

namespace zombie {
namespace network {

class ShortenedIDMap {
public:
    ShortenedIDMap();
    ~ShortenedIDMap();

    // Example API (to be filled in with actual ported methods)
    uint16_t getShortID(const std::string& longID);
    std::string getLongID(uint16_t shortID);
    void clear();

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::unordered_map<std::string, uint16_t> longToShort;
    std::unordered_map<uint16_t, std::string> shortToLong;
    uint16_t nextID;
};

} // namespace network
} // namespace zombie
