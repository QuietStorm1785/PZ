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


   {
   }
)
class TeleportToCommand : public CommandBase {
public:
    static const std::string teleportMe = "teleport me";
    static const std::string teleportUser = "Teleport user";
    std::string username;
   private float[] coords;

    public TeleportToCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.argsName;
      switch (var1) {
         case "teleport me":
            this.coords = new float[3];

            for (int var4 = 0; var4 < 3; var4++) {
               this.coords[var4] = float.parseFloat(this.getCommandArg(var4));
            }

            return this.TeleportMeToCoords();
         case "Teleport user":
            this.username = this.getCommandArg(0);
            this.coords = new float[3];

            for (int var3 = 0; var3 < 3; var3++) {
               this.coords[var3] = float.parseFloat(this.getCommandArg(var3 + 1));
            }

            return this.TeleportUserToCoords();
         default:
            return this.CommandArgumentsNotMatch();
      }
   }

    std::string TeleportMeToCoords() {
    float var1 = this.coords[0];
    float var2 = this.coords[1];
    float var3 = this.coords[2];
      if (this.connection == nullptr) {
         return "Error";
      } else {
    ByteBufferWriter var4 = this.connection.startPacket();
         PacketType.Teleport.doPacket(var4);
         var4.putByte((byte)0);
         var4.putFloat(var1);
         var4.putFloat(var2);
         var4.putFloat(var3);
         PacketType.Teleport.send(this.connection);
         if (this.connection.players[0] != nullptr && this.connection.players[0].getNetworkCharacterAI() != nullptr) {
            this.connection.players[0].getNetworkCharacterAI().resetSpeedLimiter();
         }

         LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " teleported to " + (int)var1 + "," + (int)var2 + "," + (int)var3);
         return "teleported to " + (int)var1 + "," + (int)var2 + "," + (int)var3 + " please wait two seconds to show the map around you.";
      }
   }

    std::string TeleportUserToCoords() {
    float var1 = this.coords[0];
    float var2 = this.coords[1];
    float var3 = this.coords[2];
      if (this.connection != nullptr && this.connection.accessLevel == 2 && !this.username == this.getExecutorUsername())) {
         return "An Observer can only teleport himself";
      } else {
    IsoPlayer var4 = GameServer.getPlayerByUserNameForCommand(this.username);
         if (var4 == nullptr) {
            return "Can't find player " + this.username;
         } else {
    UdpConnection var5 = GameServer.getConnectionFromPlayer(var4);
    ByteBufferWriter var6 = var5.startPacket();
            PacketType.Teleport.doPacket(var6);
            var6.putByte((byte)0);
            var6.putFloat(var1);
            var6.putFloat(var2);
            var6.putFloat(var3);
            PacketType.Teleport.send(var5);
            if (var4.getNetworkCharacterAI() != nullptr) {
               var4.getNetworkCharacterAI().resetSpeedLimiter();
            }

            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " teleported to " + (int)var1 + "," + (int)var2 + "," + (int)var3);
            return this.username + " teleported to " + (int)var1 + "," + (int)var2 + "," + (int)var3 + " please wait two seconds to show the map around you.";
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
