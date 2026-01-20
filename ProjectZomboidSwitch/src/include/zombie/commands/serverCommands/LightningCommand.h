#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class LightningCommand : public CommandBase {
public:
    public LightningCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1;
      if (this.getCommandArgsCount() == 0) {
         if (this.connection == nullptr) {
            return "Pass a username";
         }

         var1 = this.getExecutorUsername();
      } else {
         var1 = this.getCommandArg(0);
      }

    IsoPlayer var2 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var2 == nullptr) {
         return "User \"" + var1 + "\" not found";
      } else {
    int var3 = PZMath.fastfloor(var2.getX());
    int var4 = PZMath.fastfloor(var2.getY());
         ClimateManager.getInstance().transmitServerTriggerLightning(var3, var4, false, true, true);
         LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " thunder start");
         return "Lightning triggered";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
