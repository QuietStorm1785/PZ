#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSPrisonEscape : public RandomizedDeadSurvivorBase {
public:
    public RDSPrisonEscape() {
      this.name = "Prison Escape";
      this.setChance(3);
      this.setMaximumDays(90);
      this.setUnique(true);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
      this.addZombies(var1, Rand.Next(2, 4), "InmateEscaped", 0, var2);
      var1.bAlarmed = false;
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
