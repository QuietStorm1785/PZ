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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "startstorm"
)
 optional = "(\\d+)"
)
 helpText = "UI_ServerOptionDesc_StartStorm"
)
 requiredRights = 60
)
class StartStormCommand : public CommandBase {
public:
 public StartStormCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 float float0 = 24.0F;
 if (this->getCommandArgsCount() == 1) {
 try {
 float0 = Float.parseFloat(this->getCommandArg(0);
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 return "Invalid duration value";
 }
 }

 ClimateManager.getInstance().transmitServerStopWeather();
 ClimateManager.getInstance().transmitServerTriggerStorm(float0);
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " started thunderstorm");
 return "Thunderstorm started";
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
