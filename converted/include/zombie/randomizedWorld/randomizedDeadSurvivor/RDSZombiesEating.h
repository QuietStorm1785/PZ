#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/VirtualZombieManager.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Create a dead survivor in the livingroom with zombies eating him
 */
class RDSZombiesEating : public RandomizedDeadSurvivorBase {
public:
 public RDSZombiesEating() {
 this->name = "Eating zombies";
 this->setChance(7);
 this->setMaximumDays(60);
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 return IsoWorld.getZombiesEnabled() && super.isValid(def, force);
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef0 = this->getLivingRoomOrKitchen(def);
 IsoDeadBody deadBody = RandomizedDeadSurvivorBase.createRandomDeadBody(roomDef0, Rand.Next(5, 10);
 if (deadBody != nullptr) {
 VirtualZombieManager.instance.createEatingZombies(deadBody, Rand.Next(1, 3);
 RoomDef roomDef1 = this->getRoom(def, "kitchen");
 RoomDef roomDef2 = this->getRoom(def, "livingroom");
 if ("kitchen" == roomDef0.name) && roomDef2 != nullptr && Rand.Next(3) == 0) {
 deadBody = RandomizedDeadSurvivorBase.createRandomDeadBody(roomDef2, Rand.Next(5, 10);
 if (deadBody.empty()) {
 return;
 }

 VirtualZombieManager.instance.createEatingZombies(deadBody, Rand.Next(1, 3);
 }

 if ("livingroom" == roomDef0.name) && roomDef1 != nullptr && Rand.Next(3) == 0) {
 deadBody = RandomizedDeadSurvivorBase.createRandomDeadBody(roomDef1, Rand.Next(5, 10);
 if (deadBody.empty()) {
 return;
 }

 VirtualZombieManager.instance.createEatingZombies(deadBody, Rand.Next(1, 3);
 }

 def.bAlarmed = false;
 }
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
