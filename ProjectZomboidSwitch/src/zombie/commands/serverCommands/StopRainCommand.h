#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/weather/ClimateManager.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class StopRainCommand : public CommandBase {
public:
    public StopRainCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
      ClimateManager.getInstance().transmitServerStopRain();
      LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " stopped rain");
      return "Rain stopped";
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
