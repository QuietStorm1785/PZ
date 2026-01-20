#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/CommandNames.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace commands {
namespace serverCommands {


   {@CommandArgs(required = "(.+)", argName = "just port to user"), @CommandArgs(required = {"(.+)", "(.+)"}, argName = "teleport user1 to user 2")}
)
class TeleportCommand : public CommandBase {
public:
    static const std::string justToUser = "just port to user";
    static const std::string portUserToUser = "teleport user1 to user 2";
    std::string username1;
    std::string username2;

    public TeleportCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.argsName;
      switch (var1) {
         case "just port to user":
            this.username1 = this.getCommandArg(0);
            return this.TeleportMeToUser();
         case "teleport user1 to user 2":
            this.username1 = this.getCommandArg(0);
            this.username2 = this.getCommandArg(1);
            return this.TeleportUser1ToUser2();
         default:
            return this.CommandArgumentsNotMatch();
      }
   }

    std::string TeleportMeToUser() {
      if (this.connection == nullptr) {
         return "Need player to teleport to, ex /teleport user1 user2";
      } else {
    IsoPlayer var1 = GameServer.getPlayerByUserNameForCommand(this.username1);
         if (var1 != nullptr) {
            this.username1 = var1.getDisplayName();
    ByteBufferWriter var2 = this.connection.startPacket();
            PacketType.Teleport.doPacket(var2);
            var2.putByte((byte)0);
            var2.putFloat(var1.getX());
            var2.putFloat(var1.getY());
            var2.putFloat(var1.getZ());
            PacketType.Teleport.send(this.connection);
            if (this.connection.players[0] != nullptr && this.connection.players[0].getNetworkCharacterAI() != nullptr) {
               this.connection.players[0].getNetworkCharacterAI().resetSpeedLimiter();
            }

            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " teleport to " + this.username1);
            return "teleported to " + this.username1 + " please wait two seconds to show the map around you.";
         } else {
            return "Can't find player " + this.username1;
         }
      }
   }

    std::string TeleportUser1ToUser2() {
      if (this.getAccessLevel() == 2 && !this.username1 == this.getExecutorUsername())) {
         return "An Observer can only teleport himself";
      } else {
    IsoPlayer var1 = GameServer.getPlayerByUserNameForCommand(this.username1);
    IsoPlayer var2 = GameServer.getPlayerByUserNameForCommand(this.username2);
         if (var1 == nullptr) {
            return "Can't find player " + this.username1;
         } else if (var2 == nullptr) {
            return "Can't find player " + this.username2;
         } else {
            this.username1 = var1.getDisplayName();
            this.username2 = var2.getDisplayName();
    UdpConnection var3 = GameServer.getConnectionFromPlayer(var1);
            if (var3 == nullptr) {
               return "No connection for player " + this.username1;
            } else {
    ByteBufferWriter var4 = var3.startPacket();
               PacketType.Teleport.doPacket(var4);
               var4.putByte((byte)var1.PlayerIndex);
               var4.putFloat(var2.getX());
               var4.putFloat(var2.getY());
               var4.putFloat(var2.getZ());
               PacketType.Teleport.send(var3);
               if (var1.getNetworkCharacterAI() != nullptr) {
                  var1.getNetworkCharacterAI().resetSpeedLimiter();
               }

               LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " teleported " + this.username1 + " to " + this.username2);
               return "teleported " + this.username1 + " to " + this.username2;
            }
         }
      }
   }

    std::string CommandArgumentsNotMatch() {
      return this.getHelp();
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
