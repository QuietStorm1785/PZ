#include "zombie\network/PacketTypes$PacketType.h"

namespace zombie {
namespace network {

void PacketTypes$PacketType::resetStatistics() {
    // TODO: Implement resetStatistics
}

void PacketTypes$PacketType::send(UdpConnection var1) {
    // TODO: Implement send
}

void PacketTypes$PacketType::doPacket(ByteBufferWriter var1) {
    // TODO: Implement doPacket
}

short PacketTypes$PacketType::getId() {
    // TODO: Implement getId
    return 0;
}

void PacketTypes$PacketType::onServerPacket(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement onServerPacket
}

void PacketTypes$PacketType::onMainLoopHandlePacketInternal(ByteBuffer var1) {
    // TODO: Implement onMainLoopHandlePacketInternal
}

bool PacketTypes$PacketType::onGameLoadingDealWithNetData(ByteBuffer var1) {
    // TODO: Implement onGameLoadingDealWithNetData
    return false;
}

void PacketTypes$PacketType::onUnauthorized(UdpConnection var1) {
    // TODO: Implement onUnauthorized
}

} // namespace network
} // namespace zombie
