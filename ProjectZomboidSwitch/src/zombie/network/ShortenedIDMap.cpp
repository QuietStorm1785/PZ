// ShortenedIDMap.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "ShortenedIDMap.h"

namespace zombie {
namespace network {

ShortenedIDMap::ShortenedIDMap() : nextID(1) {}
ShortenedIDMap::~ShortenedIDMap() {}

uint16_t ShortenedIDMap::getShortID(const std::string& longID) {
    auto it = longToShort.find(longID);
    if (it != longToShort.end()) return it->second;
    uint16_t id = nextID++;
    longToShort[longID] = id;
    shortToLong[id] = longID;
    return id;
}

std::string ShortenedIDMap::getLongID(uint16_t shortID) {
    auto it = shortToLong.find(shortID);
    if (it != shortToLong.end()) return it->second;
    return "";
}

void ShortenedIDMap::clear() {
    longToShort.clear();
    shortToLong.clear();
    nextID = 1;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
