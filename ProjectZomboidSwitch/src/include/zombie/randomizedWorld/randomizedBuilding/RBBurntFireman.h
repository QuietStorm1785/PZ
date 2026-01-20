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
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBBurntFireman : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
    int var2 = Rand.Next(1, 4);
      var1.setHasBeenVisited(true);
    IsoCell var3 = IsoWorld.instance.CurrentCell;

      for (int var4 = var1.x - 1; var4 < var1.x2 + 1; var4++) {
         for (int var5 = var1.y - 1; var5 < var1.y2 + 1; var5++) {
            for (int var6 = 0; var6 < 8; var6++) {
    IsoGridSquare var7 = var3.getGridSquare(var4, var5, var6);
               if (var7 != nullptr && Rand.Next(100) < 70) {
                  var7.Burn(false);
               }
            }
         }
      }

      var1.setAllExplored(true);
    std::vector var8 = this.addZombies(var1, var2, "FiremanFullSuit", 35, this.getLivingRoomOrKitchen(var1));

      for (int var9 = 0; var9 < var8.size(); var9++) {
         ((IsoZombie)var8.get(var9)).getInventory().setExplored(true);
      }

    BaseVehicle var10;
      if (Rand.NextBool(2)) {
         var10 = this.spawnCarOnNearestNav("Base.PickUpVanLightsFire", var1);
      } else {
         var10 = this.spawnCarOnNearestNav("Base.PickUpTruckLightsFire", var1);
      }

      if (var10 != nullptr) {
         var10.setAlarmed(false);
      }

      if (var10 != nullptr && !var8.empty()) {
         ((IsoZombie)var8.get(Rand.Next(var8.size()))).addItemToSpawnAtDeath(var10.createVehicleKey());
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      if (!super.isValid(var1, var2)) {
    return false;
      } else {
         return var1.getRooms().size() > 20 ? false : !SpawnPoints.instance.isSpawnBuilding(var1);
      }
   }

    public RBBurntFireman() {
      this.name = "Burnt Fireman";
      this.setChance(2);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
