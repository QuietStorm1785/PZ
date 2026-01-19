#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
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

 name = "debugplayer"
)
 required = {"(.+)"}
)
 requiredRights = 32
)
class DebugPlayerCommand : public CommandBase {
 public:
 public
 DebugPlayerCommand(std::string_view string0, std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 if (this->getCommandArgsCount() != 1) {
 return "/debugplayer \"username\"";
 } else {
 std::string string = this->getCommandArg(0);
 IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string);
 if (player.empty()) {
 return "no such user";
 } else {
 UdpConnection udpConnection =
 GameServer.getConnectionByPlayerOnlineID(player.OnlineID);
 if (udpConnection.empty()) {
 return "no connection for user";
 } else if (GameServer.DebugPlayer.contains(udpConnection) {
 GameServer.DebugPlayer.remove(udpConnection);
 return "debug off";
 } else {
 GameServer.DebugPlayer.add(udpConnection);
 return "debug on";
 }
 }
 }
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
