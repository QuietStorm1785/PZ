#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpawnPoints.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBBurnt : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
      var1.setHasBeenVisited(true);
    IsoCell var2 = IsoWorld.instance.CurrentCell;

      for (int var3 = var1.x - 1; var3 < var1.x2 + 1; var3++) {
         for (int var4 = var1.y - 1; var4 < var1.y2 + 1; var4++) {
            for (int var5 = 0; var5 < 8; var5++) {
    IsoGridSquare var6 = var2.getGridSquare(var3, var4, var5);
               if (var6 != nullptr && Rand.Next(100) < 90) {
                  var6.Burn(false);
               }
            }
         }
      }

      var1.setAllExplored(true);
      var1.bAlarmed = false;
   }

    bool isValid(BuildingDef var1, bool var2) {
      if (!super.isValid(var1, var2)) {
    return false;
      } else {
         return var1.getRooms().size() > 20 ? false : !SpawnPoints.instance.isSpawnBuilding(var1);
      }
   }

    public RBBurnt() {
      this.name = "Burnt";
      this.setChance(3);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
