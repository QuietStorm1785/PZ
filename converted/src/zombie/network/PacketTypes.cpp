#include "zombie/network/PacketTypes.h"

namespace zombie {
namespace network {

void PacketTypes::doPingPacket(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement doPingPacket
}

KahluaTable PacketTypes::getPacketCounts(int int0) {
 // TODO: Implement getPacketCounts
 return nullptr;
}

void PacketTypes::call(ByteBuffer bb, short packetType) {
 // TODO: Implement call
}

void PacketTypes::call(ByteBuffer bb, UdpConnection connection, short packetType) {
 // TODO: Implement call
}

void PacketTypes::unauthorizedPacketPolicyLogUser(UdpConnection udpConnection, const std::string& string) {
 // TODO: Implement unauthorizedPacketPolicyLogUser
}

void PacketTypes::unauthorizedPacketPolicyKickUser(UdpConnection udpConnection, const std::string& string) {
 // TODO: Implement unauthorizedPacketPolicyKickUser
}

void PacketTypes::unauthorizedPacketPolicyBanUser(UdpConnection udpConnection, const std::string& string) {
 // TODO: Implement unauthorizedPacketPolicyBanUser
}

bool PacketTypes::isAuthorized(UdpConnection udpConnection, PacketTypes.PacketType packetType) {
 // TODO: Implement isAuthorized
 return false;
}

private PacketTypes::Policy(PacketTypes.PacketAuthorization.UnauthorizedPacketPolicy unauthorizedPacketPolicy) {
 // TODO: Implement Policy
 return nullptr;
}

void PacketTypes::apply(UdpConnection udpConnection, const std::string& string) {
 // TODO: Implement apply
}

void PacketTypes::call(UdpConnection var1, const std::string& var2) {
 // TODO: Implement call
}

void PacketTypes::resetStatistics() {
 // TODO: Implement resetStatistics
}

void PacketTypes::send(UdpConnection connection) {
 // TODO: Implement send
}

void PacketTypes::doPacket(ByteBufferWriter bb) {
 // TODO: Implement doPacket
}

short PacketTypes::getId() {
 // TODO: Implement getId
 return 0;
}

void PacketTypes::onServerPacket(ByteBuffer bb, UdpConnection connection) {
 // TODO: Implement onServerPacket
}

void PacketTypes::onMainLoopHandlePacketInternal(ByteBuffer bb) {
 // TODO: Implement onMainLoopHandlePacketInternal
}

bool PacketTypes::onGameLoadingDealWithNetData(ByteBuffer bb) {
 // TODO: Implement onGameLoadingDealWithNetData
 return false;
}

void PacketTypes::onUnauthorized(UdpConnection connection) {
 // TODO: Implement onUnauthorized
}

} // namespace network
} // namespace zombie
