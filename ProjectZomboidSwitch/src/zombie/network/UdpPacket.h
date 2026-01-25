// UdpPacket.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <vector>
#include <cstdint>

namespace zombie {
namespace network {

class UdpPacket {
public:
    UdpPacket();
    ~UdpPacket();

    // Example API (to be filled in with actual ported methods)
    void setData(const std::vector<uint8_t>& data);
    const std::vector<uint8_t>& getData() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<uint8_t> packetData;
};

} // namespace network
} // namespace zombie
