#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class ChopperCommand : public CommandBase {
public:
    public ChopperCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1;
      if (this.getCommandArgsCount() == 1) {
         if ("stop" == this.getCommandArg(0))) {
            IsoWorld.instance.helicopter.deactivate();
            var1 = "Chopper deactivated";
         } else if ("start" == this.getCommandArg(0))) {
            IsoWorld.instance.helicopter.pickRandomTarget();
            var1 = "Chopper activated";
         } else {
            var1 = this.getHelp();
         }
      } else {
         IsoWorld.instance.helicopter.pickRandomTarget();
         var1 = "Chopper launched";
      }

      LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " did chopper");
    return var1;
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
