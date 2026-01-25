// UdpPacketInfo.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <cstdint>
#include <vector>

namespace zombie {
namespace network {

class UdpPacketInfo {
public:
    UdpPacketInfo();
    ~UdpPacketInfo();

    // Example API (to be filled in with actual ported methods)
    void setInfo(uint32_t id, uint32_t size);
    uint32_t getId() const;
    uint32_t getSize() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    uint32_t packetId;
    uint32_t packetSize;
};

} // namespace network
} // namespace zombie
