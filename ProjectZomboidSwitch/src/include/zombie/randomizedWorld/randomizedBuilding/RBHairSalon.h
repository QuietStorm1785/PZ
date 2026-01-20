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


class RBHairSalon : public RandomizedBuildingBase {
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
                     if (Rand.NextBool(3)
                        && var8.getSurfaceOffsetNoTable() > 0.0F
                        && var6.getProperties().Val("waterAmount") == nullptr
                        && !var8.hasWater()
                        && var8.getProperties().Val("BedType") == nullptr) {
    int var9 = Rand.Next(12);
                        switch (var9) {
                           case 0:
                              this.addWorldItem("Comb", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 1:
                              this.addWorldItem("HairDyeBlonde", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 2:
                              this.addWorldItem("HairDyeBlack", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 3:
                              this.addWorldItem("HairDyeWhite", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                           case 4:
                           default:
                              break;
                           case 5:
                              this.addWorldItem("HairDyePink", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 6:
                              this.addWorldItem("HairDyeYellow", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 7:
                              this.addWorldItem("HairDyeRed", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 8:
                              this.addWorldItem("HairDyeGinger", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 9:
                              this.addWorldItem("Hairgel", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 10:
                              this.addWorldItem("Hairspray", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 11:
                              this.addWorldItem("Razor", var6, 0.5F, 0.5F, var8.getSurfaceOffsetNoTable() / 96.0F);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    bool roomValid(IsoGridSquare var1) {
      return var1.getRoom() != nullptr && "aesthetic" == var1.getRoom().getName());
   }

    bool isValid(BuildingDef var1, bool var2) {
      return var1.getRoom("aesthetic") != nullptr || var2;
   }

    public RBHairSalon() {
      this.name = "Hair Salon";
      this.setAlwaysDo(true);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
