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
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class GodModeCommand : public CommandBase {
public:
    public GodModeCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getExecutorUsername();
    std::string var2 = this.getCommandArg(0);
    std::string var3 = this.getCommandArg(1);
      if (this.getCommandArgsCount() == 2 || this.getCommandArgsCount() == 1 && !var2 == "-true") && !var2 == "-false")) {
         var1 = var2;
         if (this.connection != nullptr && this.connection.accessLevel == 2 && !var2 == var2)) {
            return "An Observer can only toggle god mode on himself";
         }
      }

    IsoPlayer var4 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var4 != nullptr) {
         var1 = var4.getDisplayName();
         if (var3 != nullptr) {
            var4.setGodMod("-true" == var3));
         } else {
            var4.setGodMod(!var4.isGodMod());
         }

         GameServer.sendPlayerExtraInfo(var4, this.connection);
         if (var4.isGodMod()) {
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " enabled godmode on " + var1);
            return "User " + var1 + " is now invincible.";
         } else {
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " disabled godmode on " + var1);
            return "User " + var1 + " is no more invincible.";
         }
      } else {
         return "User " + var1 + " not found.";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
