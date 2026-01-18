#pragma once
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
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

 name = "invisible"
)
 required = {"(.+)"},
 optional = "(-true|-false)"
 ), @CommandArgs(
 optional = "(-true|-false)"
 )
 })
 helpText = "UI_ServerOptionDesc_Invisible"
)
 requiredRights = 62
)
class InvisibleCommand : public CommandBase {
 public:
 public
 InvisibleCommand(const std::string &string0, const std::string &string1,
 const std::string &string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getExecutorUsername();
 std::string string1 = this->getCommandArg(0);
 std::string string2 = this->getCommandArg(1);
 if (this->getCommandArgsCount() == 2 ||
 this->getCommandArgsCount() == 1 && !string1 == "-true") && !string1 == "-false")) {
 string0 = string1;
 if (this->connection.accessLevel == 2 &&
 !string1 == this->getExecutorUsername())) {
 return "An Observer can only toggle invisible on himself";
 }
 }

 bool boolean0 = false;
 bool boolean1 = true;
 if ("-false" == string2) {
 boolean1 = false;
 boolean0 = true;
 }
 else if ("-true" == string2) {
 boolean0 = true;
 }

 IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string0);
 if (player != nullptr) {
 if (!boolean0) {
 boolean1 = !player.isInvisible();
 }

 string0 = player.getDisplayName();
 if (boolean0) {
 player.setInvisible(boolean1);
 } else {
 player.setInvisible(!player.isInvisible());
 boolean1 = player.isInvisible();
 }

 player.setGhostMode(boolean1);
 GameServer.sendPlayerExtraInfo(player, this->connection);
 if (boolean1) {
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() +
 " enabled invisibility on " +
 string0);
 return "User " + string0 + " is now invisible.";
 } else {
 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " disabled invisibility on " +
 string0);
 return "User " + string0 + " is no more invisible.";
 }
 } else {
 return "User " + string0 + " not found.";
 }
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
