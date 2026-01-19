#pragma once
#include "java/sql/SQLException.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/areas/SafeHouse.h"
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

 name = "releasesafehouse"
)
 helpText = "UI_ServerOptionDesc_SafeHouse"
)
 requiredRights = 63
)
class ReleaseSafehouseCommand : public CommandBase {
 public:
 public
 ReleaseSafehouseCommand(std::string_view string0,
 std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 if (this->isCommandComeFromServerConsole()) {
 return getCommandName();
 } else {
 std::string string = this->getExecutorUsername();
 IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string);
 SafeHouse safeHouse = SafeHouse.hasSafehouse(string);
 if (safeHouse != nullptr) {
 if (!safeHouse.isOwner(player) {
 return "Only owner can release safehouse";
 } else {
 safeHouse.removeSafeHouse(player);
 return "Your safehouse was released";
 }
 } else {
 return "You have no safehouse";
 }
 }
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
