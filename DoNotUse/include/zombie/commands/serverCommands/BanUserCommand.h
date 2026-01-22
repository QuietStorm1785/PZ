#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/Userlog/UserlogType.h"

namespace zombie {
namespace commands {
namespace serverCommands {


   {
   }
)
class BanUserCommand : public CommandBase {
public:
    std::string reason = "";
    static const std::string banUser = "Ban User Only";
    static const std::string banWithIP = "Ban User And IP";
    static const std::string banWithReason = "Ban User And Supply Reason";
    static const std::string banWithReasonIP = "Ban User And IP And Supply Reason";

    public BanUserCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
      if (this.hasOptionalArg(1)) {
         this.reason = this.getCommandArg(1);
      }

    bool var2 = false;
    std::string var3 = this.argsName;
      switch (var3) {
         case "Ban User And IP":
         case "Ban User And IP And Supply Reason":
            var2 = true;
         default:
            var3 = ServerWorldDatabase.instance.banUser(var1, true);
            ServerWorldDatabase.instance.addUserlog(var1, UserlogType.Banned, this.reason, this.getExecutorUsername(), 1);
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " banned user " + var1 + (this.reason != nullptr ? this.reason : ""), "IMPORTANT");
    bool var9 = false;

            for (int var5 = 0; var5 < GameServer.udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var5);
               if (var6.username == var1)) {
                  var9 = true;
                  if (SteamUtils.isSteamModeEnabled()) {
                     LoggerManager.getLogger("admin")
                        .write(
                           this.getExecutorUsername()
                              + " banned steamid "
                              + var6.steamID
                              + "("
                              + var6.username
                              + ")"
                              + (this.reason != nullptr ? this.reason : ""),
                           "IMPORTANT"
                        );
    std::string var7 = SteamUtils.convertSteamIDToString(var6.steamID);
                     ServerWorldDatabase.instance.banSteamID(var7, this.reason, true);
                  }

                  if (var2) {
                     LoggerManager.getLogger("admin")
                        .write(
                           this.getExecutorUsername() + " banned ip " + var6.ip + "(" + var6.username + ")" + (this.reason != nullptr ? this.reason : ""),
                           "IMPORTANT"
                        );
                     ServerWorldDatabase.instance.banIp(var6.ip, var1, this.reason, true);
                  }

                  if ("" == this.reason)) {
                     GameServer.kick(var6, "UI_Policy_Ban", nullptr);
                  } else {
                     GameServer.kick(var6, "You have been banned from this server for the following reason: " + this.reason, nullptr);
                  }

                  var6.forceDisconnect("command-ban-ip");
                  break;
               }
            }

            if (var9 && ServerOptions.instance.BanKickGlobalSound.getValue()) {
               GameServer.PlaySoundAtEveryPlayer("Thunder");
            }

    return var3;
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
