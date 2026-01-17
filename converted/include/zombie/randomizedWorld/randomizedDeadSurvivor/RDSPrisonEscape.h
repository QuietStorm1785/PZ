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
 * 2-3 zombies in inmate jumpsuits with some duffel bags on them with ropes,
 * duct tape, etc.
 */
class RDSPrisonEscape : public RandomizedDeadSurvivorBase {
public:
public
  RDSPrisonEscape() {
    this.name = "Prison Escape";
    this.setChance(3);
    this.setMaximumDays(90);
    this.setUnique(true);
  }

  void randomizeDeadSurvivor(BuildingDef def) {
    RoomDef roomDef = this.getLivingRoomOrKitchen(def);
    this.addZombies(def, Rand.Next(2, 4), "InmateEscaped", 0, roomDef);
    def.bAlarmed = false;
  }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
