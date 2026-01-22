#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/VirtualZombieManager.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSZombiesEating : public RandomizedDeadSurvivorBase {
public:
    public RDSZombiesEating() {
      this.name = "Eating zombies";
      this.setChance(7);
      this.setMaximumDays(60);
   }

    bool isValid(BuildingDef var1, bool var2) {
      return IsoWorld.getZombiesEnabled() && super.isValid(var1, var2);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
    IsoDeadBody var3 = RandomizedDeadSurvivorBase.createRandomDeadBody(var2, Rand.Next(5, 10));
      if (var3 != nullptr) {
         VirtualZombieManager.instance.createEatingZombies(var3, Rand.Next(1, 3));
    RoomDef var4 = this.getRoom(var1, "kitchen");
    RoomDef var5 = this.getRoom(var1, "livingroom");
         if ("kitchen" == var2.name) && var5 != nullptr && Rand.Next(3) == 0) {
            var3 = RandomizedDeadSurvivorBase.createRandomDeadBody(var5, Rand.Next(5, 10));
            if (var3 == nullptr) {
               return;
            }

            VirtualZombieManager.instance.createEatingZombies(var3, Rand.Next(1, 3));
         }

         if ("livingroom" == var2.name) && var4 != nullptr && Rand.Next(3) == 0) {
            var3 = RandomizedDeadSurvivorBase.createRandomDeadBody(var4, Rand.Next(5, 10));
            if (var3 == nullptr) {
               return;
            }

            VirtualZombieManager.instance.createEatingZombies(var3, Rand.Next(1, 3));
         }

         var1.bAlarmed = false;
      }
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
