#pragma once
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
 * Just a dead survivor in a bathroom with pistol or shotgun on him
 */
class RDSGunmanInBathroom : public RandomizedDeadSurvivorBase {
public:
  void randomizeDeadSurvivor(BuildingDef def) {
    RoomDef roomDef = super.getRoom(def, "bathroom");
    IsoDeadBody deadBody = RandomizedDeadSurvivorBase.createRandomDeadBody(
        roomDef, Rand.Next(5, 10));
    if (deadBody != nullptr) {
      deadBody.setPrimaryHandItem(super.addRandomRangedWeapon(
          deadBody.getContainer(), true, false, false));
      int int0 = Rand.Next(1, 4);

      for (int int1 = 0; int1 < int0; int1++) {
        deadBody.getContainer().AddItem(super.addRandomRangedWeapon(
            deadBody.getContainer(), true, true, true));
      }
    }
  }

public
  RDSGunmanInBathroom() {
    this.name = "Bathroom Gunman";
    this.setChance(5);
  }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
