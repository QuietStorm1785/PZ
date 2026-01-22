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


class RDSPoliceAtHouse : public RandomizedDeadSurvivorBase {
public:
    public RDSPoliceAtHouse() {
      this.name = "Police at House";
      this.setChance(4);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
      this.addZombies(var1, Rand.Next(2, 4), nullptr, 0, var2);
    std::vector var3 = this.addZombies(var1, Rand.Next(1, 3), "Police", nullptr, var2);
    BaseVehicle var4 = this.spawnCarOnNearestNav("Base.CarLightsPolice", var1);
      if (var4 != nullptr) {
    IsoGridSquare var5 = var4.getSquare().getCell().getGridSquare(var4.getSquare().x - 2, var4.getSquare().y - 2, 0);
    std::vector var6 = this.addZombiesOnSquare(2, "Police", nullptr, var5);
         createRandomDeadBody(var2, Rand.Next(7, 10));
         createRandomDeadBody(var2, Rand.Next(7, 10));
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
