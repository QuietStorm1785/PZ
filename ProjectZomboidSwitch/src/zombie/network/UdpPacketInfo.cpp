// UdpPacketInfo.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "UdpPacketInfo.h"

namespace zombie {
namespace network {

UdpPacketInfo::UdpPacketInfo() : packetId(0), packetSize(0) {}
UdpPacketInfo::~UdpPacketInfo() {}

void UdpPacketInfo::setInfo(uint32_t id, uint32_t size) {
    packetId = id;
    packetSize = size;
}

uint32_t UdpPacketInfo::getId() const {
    return packetId;
}

uint32_t UdpPacketInfo::getSize() const {
    return packetSize;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
