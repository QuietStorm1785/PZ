#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Well, it's friday the 13th... Basically.
 */
class RDSHockeyPsycho : public RandomizedDeadSurvivorBase {
public:
 public RDSHockeyPsycho() {
 this->name = "Hockey Psycho (friday 13th!)";
 this->setUnique(true);
 this->setChance(1);
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef = this->getLivingRoomOrKitchen(def);
 std::vector arrayList = this->addZombies(def, 1, "HockeyPsycho", 0, roomDef);
 if (arrayList != nullptr && !arrayList.empty()) {
 IsoZombie zombie0 = (IsoZombie)arrayList.get(0);
 zombie0.addBlood(BloodBodyPartType.Head, true, true, true);

 for (int int0 = 0; int0 < 10; int0++) {
 zombie0.addBlood(nullptr, true, false, true);
 zombie0.addDirt(nullptr, Rand.Next(0, 3), true);
 }
 }

 for (int int1 = 0; int1 < 10; int1++) {
 IsoDeadBody deadBody = createRandomDeadBody(this->getRandomRoom(def, 2), Rand.Next(5, 20);
 if (deadBody != nullptr) {
 this->addTraitOfBlood(IsoDirections.getRandom(), 15, (int)deadBody.x, (int)deadBody.y, (int)deadBody.z);
 this->addTraitOfBlood(IsoDirections.getRandom(), 15, (int)deadBody.x, (int)deadBody.y, (int)deadBody.z);
 this->addTraitOfBlood(IsoDirections.getRandom(), 15, (int)deadBody.x, (int)deadBody.y, (int)deadBody.z);
 }
 }

 def.bAlarmed = false;
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
