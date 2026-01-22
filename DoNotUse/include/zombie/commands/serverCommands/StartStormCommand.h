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
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/weather/ClimateManager.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class StartStormCommand : public CommandBase {
public:
    public StartStormCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    float var1 = 24.0F;
      if (this.getCommandArgsCount() == 1) {
         try {
            var1 = float.parseFloat(this.getCommandArg(0));
         } catch (Throwable var3) {
            ExceptionLogger.logException(var3);
            return "Invalid duration value";
         }
      }

      ClimateManager.getInstance().transmitServerStopWeather();
      ClimateManager.getInstance().transmitServerTriggerStorm(var1);
      LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " started thunderstorm");
      return "Thunderstorm started";
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
