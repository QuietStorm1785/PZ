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


class RDSTinFoilHat : public RandomizedDeadSurvivorBase {
public:
    public RDSTinFoilHat() {
      this.name = "Tin foil hat family";
      this.setUnique(true);
      this.setChance(2);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
      this.addZombies(var1, Rand.Next(2, 5), "TinFoilHat", nullptr, var2);
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
