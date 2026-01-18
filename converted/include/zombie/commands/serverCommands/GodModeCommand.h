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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "godmod"
 ), @CommandName(
 name = "godmode"
 )})
 required = {"(.+)"},
 optional = "(-true|-false)"
 ), @CommandArgs(
 optional = "(-true|-false)"
 )})
 helpText = "UI_ServerOptionDesc_GodMod"
)
 requiredRights = 62
)
class GodModeCommand : public CommandBase {
public:
 public GodModeCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getExecutorUsername();
 std::string string1 = this->getCommandArg(0);
 std::string string2 = this->getCommandArg(1);
 if (this->getCommandArgsCount() == 2 || this->getCommandArgsCount() == 1 && !string1 == "-true") && !string1 == "-false")) {
 string0 = string1;
 if (this->connection != nullptr && this->connection.accessLevel == 2 && !string1 == string1) {
 return "An Observer can only toggle god mode on himself";
 }
 }

 IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string0);
 if (player != nullptr) {
 string0 = player.getDisplayName();
 if (string2 != nullptr) {
 player.setGodMod("-true" == string2);
 } else {
 player.setGodMod(!player.isGodMod());
 }

 GameServer.sendPlayerExtraInfo(player, this->connection);
 if (player.isGodMod()) {
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " enabled godmode on " + string0);
 return "User " + string0 + " is now invincible.";
 } else {
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " disabled godmode on " + string0);
 return "User " + string0 + " is no more invincible.";
 }
 } else {
 return "User " + string0 + " not found.";
 }
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
