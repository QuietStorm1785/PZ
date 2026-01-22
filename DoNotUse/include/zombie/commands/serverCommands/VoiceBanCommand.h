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
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class VoiceBanCommand : public CommandBase {
public:
    public VoiceBanCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getExecutorUsername();
      if (this.getCommandArgsCount() == 2
         || this.getCommandArgsCount() == 1 && !this.getCommandArg(0) == "-true") && !this.getCommandArg(0) == "-false")) {
         var1 = this.getCommandArg(0);
      }

    bool var2 = true;
      if (this.getCommandArgsCount() > 0) {
         var2 = !this.getCommandArg(this.getCommandArgsCount() - 1) == "-false");
      }

    IsoPlayer var3 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var3 != nullptr) {
         var1 = var3.getDisplayName();
         VoiceManager.instance.VMServerBan(var3.OnlineID, var2);
         if (var2) {
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " ban voice " + var1);
            return "User " + var1 + " voice is banned.";
         } else {
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " unban voice " + var1);
            return "User " + var1 + " voice is unbanned.";
         }
      } else {
         return "User " + var1 + " not found.";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
