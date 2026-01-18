#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Need a garage with a size of at least 10 tiles Spawn some rocker zombies & music instruments on ground & shelves Corpse with a guitar in his hand
 */
class RDSBandPractice : public RandomizedDeadSurvivorBase {
public:
 private ArrayList<String> instrumentsList = std::make_unique<ArrayList<>>();

 public RDSBandPractice() {
 this->name = "Band Practice";
 this->setChance(10);
 this->setMaximumDays(60);
 this->instrumentsList.add("GuitarAcoustic");
 this->instrumentsList.add("GuitarElectricBlack");
 this->instrumentsList.add("GuitarElectricBlue");
 this->instrumentsList.add("GuitarElectricRed");
 this->instrumentsList.add("GuitarElectricBassBlue");
 this->instrumentsList.add("GuitarElectricBassBlack");
 this->instrumentsList.add("GuitarElectricBassRed");
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 this->spawnItemsInContainers(def, "BandPractice", 90);
 RoomDef roomDef = this->getRoom(def, "garagestorage");
 if (roomDef.empty()) {
 roomDef = this->getRoom(def, "shed");
 }

 if (roomDef.empty()) {
 roomDef = this->getRoom(def, "garage");
 }

 this->addZombies(def, Rand.Next(2, 4), "Rocker", 20, roomDef);
 IsoGridSquare square = getRandomSpawnSquare(roomDef);
 if (square != nullptr) {
 square.AddWorldInventoryItem(PZArrayUtil.pickRandom(this->instrumentsList), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 if (Rand.Next(4) == 0) {
 square.AddWorldInventoryItem(PZArrayUtil.pickRandom(this->instrumentsList), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 }

 if (Rand.Next(4) == 0) {
 square.AddWorldInventoryItem(PZArrayUtil.pickRandom(this->instrumentsList), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 }

 def.bAlarmed = false;
 }
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
 if (player.getSquare() != nullptr && player.getSquare().getBuilding() != nullptr && player.getSquare().getBuilding().def == def) {
 return false;
 }
 }
 }

 bool boolean0 = false;

 for (int int1 = 0; int1 < def.rooms.size(); int1++) {
 RoomDef roomDef = def.rooms.get(int1);
 if (("garagestorage" == roomDef.name) || "shed" == roomDef.name) || "garage" == roomDef.name) && roomDef.area >= 9) {
 boolean0 = true;
 break;
 }
 }

 if (!boolean0) {
 this->debugLine = "No shed/garage or is too small";
 }

 return boolean0;
 }
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
