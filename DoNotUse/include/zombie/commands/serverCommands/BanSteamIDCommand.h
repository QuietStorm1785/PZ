#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class BanSteamIDCommand : public CommandBase {
public:
    public BanSteamIDCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
      if (!SteamUtils.isSteamModeEnabled()) {
         return "Server is not in Steam mode";
      } else if (!SteamUtils.isValidSteamID(var1)) {
         return "Expected SteamID but got \"" + var1 + "\"";
      } else {
         LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " banned SteamID " + var1, "IMPORTANT");
         ServerWorldDatabase.instance.banSteamID(var1, "", true);
    long var2 = SteamUtils.convertStringToSteamID(var1);

         for (int var4 = 0; var4 < GameServer.udpEngine.connections.size(); var4++) {
    UdpConnection var5 = (UdpConnection)GameServer.udpEngine.connections.get(var4);
            if (var5.steamID == var2) {
               GameServer.kick(var5, "UI_Policy_Ban", nullptr);
               var5.forceDisconnect("command-ban-sid");
               break;
            }
         }

         return "SteamID " + var1 + " is now banned";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
