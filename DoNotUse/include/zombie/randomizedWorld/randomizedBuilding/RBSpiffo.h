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
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBSpiffo : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
    IsoCell var2 = IsoWorld.instance.CurrentCell;

      for (int var3 = var1.x - 1; var3 < var1.x2 + 1; var3++) {
         for (int var4 = var1.y - 1; var4 < var1.y2 + 1; var4++) {
            for (int var5 = 0; var5 < 8; var5++) {
    IsoGridSquare var6 = var2.getGridSquare(var3, var4, var5);
               if (var6 != nullptr && this.roomValid(var6)) {
                  for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var6.getObjects().get(var7);
                     if (Rand.NextBool(2) && this.isTableFor3DItems(var8, var6)) {
                        System.out.println("adding item on table " + var8.getSprite().getName() + " coords: " + var6.x + "," + var6.y);
                        if (Rand.NextBool(2)) {
                           this.addWorldItem("Burger", var6, var8);
                        }

                        if (Rand.NextBool(2)) {
                           this.addWorldItem("Fries", var6, var8);
                        }

                        if (Rand.NextBool(2)) {
                           this.addWorldItem("Ketchup", var6, var8);
                        }

                        if (Rand.NextBool(3)) {
                           this.addWorldItem("Fork", var6, var8);
                        }

                        if (Rand.NextBool(3)) {
                           this.addWorldItem("ButterKnife", var6, var8);
                        }

                        if (Rand.NextBool(30)) {
                           this.addWorldItem("MugSpiffo", var6, var8);
                        }
                        break;
                     }
                  }
               }
            }
         }
      }
   }

    bool roomValid(IsoGridSquare var1) {
      return var1.getRoom() != nullptr && ("spiffo_dining" == var1.getRoom().getName()) || "burgerkitchen" == var1.getRoom().getName()));
   }

    bool isValid(BuildingDef var1, bool var2) {
      return var1.getRoom("spiffo_dining") != nullptr || var1.getRoom("burgerkitchen") != nullptr || var2;
   }

    public RBSpiffo() {
      this.name = "Spiffo Restaurant";
      this.setAlwaysDo(true);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
