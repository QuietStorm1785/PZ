#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Create a dead survivor somewhere with lot of modified guns/ammo on him
 */
class RDSGunslinger : public RandomizedDeadSurvivorBase {
public:
 void randomizeDeadSurvivor(BuildingDef def) {
 IsoGridSquare square = def.getFreeSquareInRoom();
 if (square != nullptr) {
 IsoDeadBody deadBody = RandomizedDeadSurvivorBase.createRandomDeadBody(square.getX(), square.getY(), square.getZ(), nullptr, 0);
 if (deadBody != nullptr) {
 deadBody.setPrimaryHandItem(super.addRandomRangedWeapon(deadBody.getContainer(), true, false, false);
 int int0 = Rand.Next(1, 4);

 for (int int1 = 0; int1 < int0; int1++) {
 deadBody.getContainer().AddItem(super.addRandomRangedWeapon(deadBody.getContainer(), true, true, true);
 }
 }
 }
 }

 public RDSGunslinger() {
 this->name = "Gunslinger";
 this->setChance(5);
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
