#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/CommandNames.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/Userlog/UserlogType.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class KickUserCommand : public CommandBase {
public:
    std::string reason = "";

    public KickUserCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
      if (this.hasOptionalArg(1)) {
         this.reason = this.getCommandArg(1);
      }

      LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " kicked user " + var1);
      ServerWorldDatabase.instance.addUserlog(var1, UserlogType.Kicked, this.reason, this.getExecutorUsername(), 1);
    bool var2 = false;

      for (int var3 = 0; var3 < GameServer.udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)GameServer.udpEngine.connections.get(var3);

         for (int var5 = 0; var5 < 4; var5++) {
            if (var1 == var4.usernames[var5])) {
               var2 = true;
               if ("" == this.reason)) {
                  GameServer.kick(var4, "UI_Policy_Kick", nullptr);
               } else {
                  GameServer.kick(var4, "You have been kicked from this server for the following reason: " + this.reason, nullptr);
               }

               var4.forceDisconnect("command-kick");
               GameServer.addDisconnect(var4);
               break;
            }
         }
      }

      if (var2 && ServerOptions.instance.BanKickGlobalSound.getValue()) {
         GameServer.PlaySoundAtEveryPlayer("RumbleThunder");
      }

      return var2 ? "User " + var1 + " kicked." : "User " + var1 + " doesn't exist.";
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
