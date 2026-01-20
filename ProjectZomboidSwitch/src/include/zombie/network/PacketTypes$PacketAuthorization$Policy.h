#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/PacketTypes/PacketAuthorization.h"
#include "zombie/network/PacketTypes/PacketAuthorization/UnauthorizedPacketPolicy.h"

namespace zombie {
namespace network {


enum class PacketTypes {
   Log(PacketAuthorization::unauthorizedPacketPolicyLogUser),
   Kick(PacketAuthorization::unauthorizedPacketPolicyKickUser),
   Ban(PacketAuthorization::unauthorizedPacketPolicyBanUser);

    const UnauthorizedPacketPolicy policy;

   private PacketTypes$PacketAuthorization$Policy(UnauthorizedPacketPolicy var3) {
      this.policy = var3;
   }

    void apply(UdpConnection var1, const std::string& var2) {
      this.policy.call(var1, var2);
   }
}
} // namespace network
} // namespace zombie
