#pragma once
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
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

 name = "thunder"
)
 optional = "(.+)"
)
 helpText = "UI_ServerOptionDesc_Thunder"
)
 requiredRights = 60
)
class ThunderCommand : public CommandBase {
 public:
 public
 ThunderCommand(std::string_view string0, std::string_view string1,
 std::string_view string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string;
 if (this->getCommandArgsCount() == 0) {
 if (this->connection.empty()) {
 return "Pass a username";
 }

 string = this->getExecutorUsername();
 } else {
 string = this->getCommandArg(0);
 }

 IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string);
 if (player.empty()) {
 return "User \"" + string + "\" not found";
 } else {
 int int0 = PZMath.fastfloor(player.getX());
 int int1 = PZMath.fastfloor(player.getY());
 ClimateManager.getInstance().transmitServerTriggerLightning(
 int0, int1, false, false, true);
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() +
 " thunder start");
 return "Thunder triggered";
 }
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
