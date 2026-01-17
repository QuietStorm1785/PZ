#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
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
 * Zombies family with tin foil hat
 */
class RDSTinFoilHat : public RandomizedDeadSurvivorBase {
public:
public
  RDSTinFoilHat() {
    this.name = "Tin foil hat family";
    this.setUnique(true);
    this.setChance(2);
  }

  void randomizeDeadSurvivor(BuildingDef def) {
    RoomDef roomDef = this.getLivingRoomOrKitchen(def);
    this.addZombies(def, Rand.Next(2, 5), "TinFoilHat", nullptr, roomDef);
  }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
