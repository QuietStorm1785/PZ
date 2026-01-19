package zombie.network;

import zombie.SystemDisabler;
import zombie.commands.PlayerType;
import zombie.core.Core;
import zombie.core.raknet.UdpConnection;
import zombie.core.znet.SteamUtils;
import zombie.debug.DebugLog;
import zombie.network.PacketTypes.PacketType;
import zombie.network.Userlog.UserlogType;

class PacketTypes$PacketAuthorization {
   private PacketTypes$PacketAuthorization() {
   }

   private static void unauthorizedPacketPolicyLogUser(UdpConnection var0, String var1) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() && PacketValidator.checkUser(var0)) {
         PacketValidator.doLogUser(var0, UserlogType.UnauthorizedPacket, var1, "Type8");
      }
   }

   private static void unauthorizedPacketPolicyKickUser(UdpConnection var0, String var1) {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() && PacketValidator.checkUser(var0)) {
         PacketValidator.doKickUser(var0, var1, "Type8", null);
      }
   }

   private static void unauthorizedPacketPolicyBanUser(UdpConnection var0, String var1) throws Exception {
      if (ServerOptions.instance.AntiCheatProtectionType8.getValue() && PacketValidator.checkUser(var0)) {
         PacketValidator.doBanUser(var0, var1, "Type8");
      }
   }

   private static boolean isAuthorized(UdpConnection var0, PacketType var1) throws Exception {
      boolean var2 = (var0.accessLevel & var1.requiredAccessLevel) != 0;
      if ((!var2 || var1.serverProcess == null) && (!Core.bDebug || SystemDisabler.doKickInDebug)) {
         DebugLog.Multiplayer
            .warn(
               String.format(
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
