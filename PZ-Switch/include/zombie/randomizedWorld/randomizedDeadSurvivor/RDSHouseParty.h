#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Zombies in party outfit, some food scattered around
 */
class RDSHouseParty : public RandomizedDeadSurvivorBase {
public:
 ArrayList<String> items = std::make_unique<ArrayList<>>();

public
 RDSHouseParty() {
 this->name = "House Party";
 this->setChance(4);
 this->items.add("Base.Crisps");
 this->items.add("Base.Crisps2");
 this->items.add("Base.Crisps3");
 this->items.add("Base.Pop");
 this->items.add("Base.Pop2");
 this->items.add("Base.Pop3");
 this->items.add("Base.Cupcake");
 this->items.add("Base.Cupcake");
 this->items.add("Base.CakeSlice");
 this->items.add("Base.CakeSlice");
 this->items.add("Base.CakeSlice");
 this->items.add("Base.CakeSlice");
 this->items.add("Base.CakeSlice");
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 this->debugLine = "";
 if (GameClient.bClient) {
 return false;
 } else if (def.isAllExplored() && !force) {
 return false;
 } else {
 if (!force) {
 for (int int0 = 0; int0 < GameServer.Players.size(); int0++) {
 IsoPlayer player = GameServer.Players.get(int0);
 if (player.getSquare() != nullptr &&
 player.getSquare().getBuilding() != nullptr &&
 player.getSquare().getBuilding().def == def) {
 return false;
 }
 }
 }

 if (this->getRoom(def, "livingroom") != nullptr) {
 return true;
 } else {
 this->debugLine = "No living room";
 return false;
 }
 }
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef = this->getRoom(def, "livingroom");
 this->addZombies(def, Rand.Next(5, 8), "Party", nullptr, roomDef);
 this->addRandomItemsOnGround(roomDef, this->items, Rand.Next(4, 7);
 def.bAlarmed = false;
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
