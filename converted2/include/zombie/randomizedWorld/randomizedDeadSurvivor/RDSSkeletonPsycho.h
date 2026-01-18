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
 * Create skeleton corpses in a bedroom with one zombie as doctor
 */
class RDSSkeletonPsycho : public RandomizedDeadSurvivorBase {
public:
public
  RDSSkeletonPsycho() {
    this.name = "Skeleton Psycho";
    this.setChance(1);
    this.setMinimumDays(120);
    this.setUnique(true);
  }

  void randomizeDeadSurvivor(BuildingDef def) {
    RoomDef roomDef = this.getRoom(def, "bedroom");
    int int0 = Rand.Next(3, 7);

    for (int int1 = 0; int1 < int0; int1++) {
      IsoDeadBody deadBody = super.createSkeletonCorpse(roomDef);
      if (deadBody != nullptr) {
        super.addBloodSplat(deadBody.getCurrentSquare(), Rand.Next(7, 12));
      }
    }

    std::vector arrayList = super.addZombies(def, 1, "Doctor", null, roomDef);
    if (!arrayList.isEmpty()) {
      for (int int2 = 0; int2 < 8; int2++) {
        ((IsoZombie)arrayList.get(0)).addBlood(nullptr, false, true, false);
      }

      def.bAlarmed = false;
    }
  }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
