#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSPrisonEscapeWithPolice : public RandomizedDeadSurvivorBase {
public:
    public RDSPrisonEscapeWithPolice() {
      this.name = "Prison Escape with Police";
      this.setChance(2);
      this.setMaximumDays(90);
      this.setUnique(true);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
      this.addZombies(var1, Rand.Next(2, 4), "InmateEscaped", 0, var2);
    std::vector var3 = this.addZombies(var1, Rand.Next(2, 4), "Police", nullptr, var2);
    BaseVehicle var4 = this.spawnCarOnNearestNav("Base.CarLightsPolice", var1);
      if (var4 != nullptr) {
         var4.setAlarmed(false);
      }

      if (var4 != nullptr) {
    IsoGridSquare var5 = var4.getSquare().getCell().getGridSquare(var4.getSquare().x - 2, var4.getSquare().y - 2, 0);
    std::vector var6 = this.addZombiesOnSquare(3, "Police", nullptr, var5);
         if (!var3.empty()) {
            var3.addAll(var6);
            ((IsoZombie)var3.get(Rand.Next(var3.size()))).addItemToSpawnAtDeath(var4.createVehicleKey());
            var1.bAlarmed = false;
         }
      }
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
