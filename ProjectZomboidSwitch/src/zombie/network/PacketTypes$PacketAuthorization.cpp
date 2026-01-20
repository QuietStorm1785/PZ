#include <string>
#include "zombie\network/PacketTypes$PacketAuthorization.h"

namespace zombie {
namespace network {

void PacketTypes$PacketAuthorization::unauthorizedPacketPolicyLogUser(UdpConnection var0, const std::string& var1) {
    // TODO: Implement unauthorizedPacketPolicyLogUser
}

void PacketTypes$PacketAuthorization::unauthorizedPacketPolicyKickUser(UdpConnection var0, const std::string& var1) {
    // TODO: Implement unauthorizedPacketPolicyKickUser
}

void PacketTypes$PacketAuthorization::unauthorizedPacketPolicyBanUser(UdpConnection var0, const std::string& var1) {
    // TODO: Implement unauthorizedPacketPolicyBanUser
}

bool PacketTypes$PacketAuthorization::isAuthorized(UdpConnection var0, PacketType var1) {
    // TODO: Implement isAuthorized
    return false;
}

} // namespace network
} // namespace zombie
