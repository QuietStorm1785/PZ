#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SystemDisabler.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/Userlog/UserlogType.h"

namespace zombie {
namespace network {


class PacketTypes {
public:
   private PacketTypes$PacketAuthorization() {
   }

    static void unauthorizedPacketPolicyLogUser(UdpConnection var0, const std::string& var1) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() && PacketValidator.checkUser(var0)) {
         PacketValidator.doLogUser(var0, UserlogType.UnauthorizedPacket, var1, "Type8");
      }
   }

    static void unauthorizedPacketPolicyKickUser(UdpConnection var0, const std::string& var1) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() && PacketValidator.checkUser(var0)) {
         PacketValidator.doKickUser(var0, var1, "Type8", nullptr);
      }
   }

    static void unauthorizedPacketPolicyBanUser(UdpConnection var0, const std::string& var1) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() && PacketValidator.checkUser(var0)) {
         PacketValidator.doBanUser(var0, var1, "Type8");
      }
   }

    static bool isAuthorized(UdpConnection var0, PacketType var1) {
    bool var2 = (var0.accessLevel & var1.requiredAccessLevel) != 0;
      if ((!var2 || var1.serverProcess == nullptr) && (!Core.bDebug || SystemDisabler.doKickInDebug)) {
         DebugLog.Multiplayer
            .warn(
               std::string.format(
                  "Unauthorized packet %s (%s) was received from user=\"%s\" (%s) ip %s %s",
                  var1.name(),
                  PlayerType.toString(var1.requiredAccessLevel),
                  var0.username,
                  PlayerType.toString(var0.accessLevel),
                  var0.ip,
                  SteamUtils.isSteamModeEnabled() ? var0.steamID : ""
               )
            );
         var1.unauthorizedPacketPolicy.apply(var0, var1.name());
      }

    return var2;
   }
}
} // namespace network
} // namespace zombie
