#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/chat/ChatServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class SetAccessLevelCommand : public CommandBase {
public:
    public SetAccessLevelCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
    std::string var2 = "none" == this.getCommandArg(1)) ? "" : this.getCommandArg(1);
    return update();
   }

    static std::string update(const std::string& var0, UdpConnection var1, const std::string& var2, const std::string& var3) {
      if ((var1 == nullptr || !var1.isCoopHost) && !ServerWorldDatabase.instance.containsUser(var2) && var1 != nullptr) {
         return "User \"" + var2 + "\" is not in the whitelist, use /adduser first";
      } else {
    IsoPlayer var4 = GameServer.getPlayerByUserName(var2);
    uint8_t var5 = PlayerType.fromString(var3.trim().toLowerCase());
         if (var1 != nullptr && var1.accessLevel == 16 && var5 == 32) {
            return "Moderators can't set Admin access level";
         } else if (var5 == 0) {
            return "Access Level '" + var5 + "' unknown, list of access level: player, admin, moderator, overseer, gm, observer";
         } else {
            if (var4 != nullptr) {
               if (var4.networkAI != nullptr) {
                  var4.networkAI.setCheckAccessLevelDelay(5000L);
               }

    UdpConnection var6 = GameServer.getConnectionFromPlayer(var4);
    uint8_t var7;
               if (var6 != nullptr) {
                  var7 = var6.accessLevel;
               } else {
                  var7 = PlayerType.fromString(var4.accessLevel.toLowerCase());
               }

               if (var7 != var5) {
                  if (var5 == 32) {
                     ChatServer.getInstance().joinAdminChat(var4.OnlineID);
                  } else if (var7 == 32 && var5 != 32) {
                     ChatServer.getInstance().leaveAdminChat(var4.OnlineID);
                  }
               }

               if (var7 != 1 && var5 == 1) {
                  var4.setGhostMode(false);
                  var4.setNoClip(false);
               }

               var4.accessLevel = PlayerType.toString(var5);
               if (var6 != nullptr) {
                  var6.accessLevel = var5;
               }

               if ((var5 & 62) != 0) {
                  var4.setGodMod(true);
                  var4.setGhostMode(true);
                  var4.setInvisible(true);
               } else {
                  var4.setGodMod(false);
                  var4.setGhostMode(false);
                  var4.setInvisible(false);
               }

               GameServer.sendPlayerExtraInfo(var4, nullptr);
            }

            LoggerManager.getLogger("admin").write(var0 + " granted " + var5 + " access level on " + var2);
            return var1 != nullptr && var1.isCoopHost
               ? "Your access level is now: " + var5
               : ServerWorldDatabase.instance.setAccessLevel(var2, PlayerType.toString(var5));
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
