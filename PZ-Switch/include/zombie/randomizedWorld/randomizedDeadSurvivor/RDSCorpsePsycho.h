#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"
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
 * Create corpses in a kitchen with one zombie as doctor
 */
class RDSCorpsePsycho : public RandomizedDeadSurvivorBase {
public:
public
 RDSCorpsePsycho() {
 this->name = "Corpse Psycho";
 this->setChance(1);
 this->setMinimumDays(120);
 this->setUnique(true);
 }

 void randomizeDeadSurvivor(BuildingDef def) {
 RoomDef roomDef = this->getRoom(def, "kitchen");
 int int0 = Rand.Next(3, 7);

 for (int int1 = 0; int1 < int0; int1++) {
 IsoDeadBody deadBody = RandomizedDeadSurvivorBase.createRandomDeadBody(
 roomDef, Rand.Next(5, 10);
 if (deadBody != nullptr) {
 super.addBloodSplat(deadBody.getCurrentSquare(), Rand.Next(7, 12);
 }
 }

 std::vector arrayList = super.addZombies(def, 1, "Doctor", nullptr, roomDef);
 if (!arrayList.empty()) {
 for (int int2 = 0; int2 < 8; int2++) {
 ((IsoZombie)arrayList.get(0).addBlood(nullptr, false, true, false);
 }

 def.bAlarmed = false;
 }
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
