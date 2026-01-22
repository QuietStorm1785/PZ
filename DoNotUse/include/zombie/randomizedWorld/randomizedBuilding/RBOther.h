#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpawnPoints.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBOther : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
      var1.setHasBeenVisited(true);
      var1.setAllExplored(true);
    IsoCell var2 = IsoWorld.instance.CurrentCell;

      for (int var3 = var1.x - 1; var3 < var1.x2 + 1; var3++) {
         for (int var4 = var1.y - 1; var4 < var1.y2 + 1; var4++) {
            for (int var5 = 0; var5 < 8; var5++) {
    IsoGridSquare var6 = var2.getGridSquare(var3, var4, var5);
               if (var6 != nullptr) {
                  for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var6.getObjects().get(var7);
                     if (var8.getContainer() != nullptr) {
                        var8.getContainer().emptyIt();
                        var8.getContainer().AddItems("Base.ToiletPaper", Rand.Next(10, 30));
                        ItemPickerJava.updateOverlaySprite(var8);
                     }
                  }
               }
            }
         }
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      if (!super.isValid(var1, var2)) {
    return false;
      } else {
         return var1.getRooms().size() > 10 ? false : !SpawnPoints.instance.isSpawnBuilding(var1);
      }
   }

    public RBOther() {
      this.name = "Other";
      this.setChance(1);
      this.setUnique(true);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
