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
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class InvisibleCommand : public CommandBase {
public:
    public InvisibleCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getExecutorUsername();
    std::string var2 = this.getCommandArg(0);
    std::string var3 = this.getCommandArg(1);
      if (this.getCommandArgsCount() == 2 || this.getCommandArgsCount() == 1 && !var2 == "-true") && !var2 == "-false")) {
         var1 = var2;
         if (this.connection.accessLevel == 2 && !var2 == this.getExecutorUsername())) {
            return "An Observer can only toggle invisible on himself";
         }
      }

    bool var4 = false;
    bool var5 = true;
      if ("-false" == var3)) {
         var5 = false;
         var4 = true;
      } else if ("-true" == var3)) {
         var4 = true;
      }

    IsoPlayer var6 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var6 != nullptr) {
         if (!var4) {
            var5 = !var6.isInvisible();
         }

         var1 = var6.getDisplayName();
         if (var4) {
            var6.setInvisible(var5);
         } else {
            var6.setInvisible(!var6.isInvisible());
            var5 = var6.isInvisible();
         }

         var6.setGhostMode(var5);
         GameServer.sendPlayerExtraInfo(var6, this.connection);
         if (var5) {
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " enabled invisibility on " + var1);
            return "User " + var1 + " is now invisible.";
         } else {
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " disabled invisibility on " + var1);
            return "User " + var1 + " is no more invisible.";
         }
      } else {
         return "User " + var1 + " not found.";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
