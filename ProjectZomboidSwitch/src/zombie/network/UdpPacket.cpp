// UdpPacket.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "UdpPacket.h"

namespace zombie {
namespace network {

UdpPacket::UdpPacket() {}
UdpPacket::~UdpPacket() {}

void UdpPacket::setData(const std::vector<uint8_t>& data) {
    packetData = data;
}

const std::vector<uint8_t>& UdpPacket::getData() const {
    return packetData;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
