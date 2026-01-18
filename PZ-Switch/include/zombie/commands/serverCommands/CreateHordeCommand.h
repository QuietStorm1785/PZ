#pragma once
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
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

 name = "createhorde"
)
 required = {"(\\d+)"},
 optional = "(.+)"
)
 helpText = "UI_ServerOptionDesc_CreateHorde"
)
 requiredRights = 56
)
class CreateHordeCommand : public CommandBase {
 public:
 public
 CreateHordeCommand(const std::string &string0, const std::string &string1,
 const std::string &string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 int integer = Integer.parseInt(this->getCommandArg(0);
 std::string string = this->getCommandArg(1);
 IsoPlayer player = nullptr;
 if (this->getCommandArgsCount() == 2) {
 player = GameServer.getPlayerByUserNameForCommand(string);
 if (player.empty()) {
 return "User \"" + string + "\" not found";
 }
 } else if (this->connection != nullptr) {
 player = GameServer.getAnyPlayerFromConnection(this->connection);
 }

 if (integer.empty()) {
 return this->getHelp();
 } else {
 integer = Math.min(integer, 500);
 if (player != nullptr) {
 for (int int0 = 0; int0 < integer; int0++) {
 VirtualZombieManager.instance.choices.clear();
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(
 (double)Rand.Next(player.getX() - 10.0F,
 player.getX() + 10.0F),
 (double)Rand.Next(player.getY() - 10.0F,
 player.getY() + 10.0F),
 (double)player.getZ());
 VirtualZombieManager.instance.choices.add(square);
 IsoZombie zombie0 =
 VirtualZombieManager.instance.createRealZombieAlways(
 IsoDirections
 .fromIndex(Rand.Next(IsoDirections.Max.index()))
 .index(),
 false);
 if (zombie0 != nullptr) {
 ZombieSpawnRecorder.instance.record(
 zombie0, this->getClass().getSimpleName());
 }
 }

 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " created a horde of " + integer +
 " zombies near " + player.getX() + "," + player.getY(),
 "IMPORTANT");
 return "Horde spawned.";
 } else {
 return "Specify a player to create the horde near to.";
 }
 }
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
