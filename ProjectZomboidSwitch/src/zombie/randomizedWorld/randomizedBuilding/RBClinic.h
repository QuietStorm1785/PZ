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


class RBClinic : public RandomizedBuildingBase {
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
                     if (Rand.NextBool(2)
                        && var8.getSurfaceOffsetNoTable() > 0.0F
                        && var8.getContainer() == nullptr
                        && var6.getProperties().Val("waterAmount") == nullptr
                        && !var8.hasWater()) {
    int var9 = Rand.Next(1, 3);

                        for (int var10 = 0; var10 < var9; var10++) {
    int var11 = Rand.Next(12);
                           switch (var11) {
                              case 0:
                                 this.addWorldItem("Scalpel", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 1:
                                 this.addWorldItem("Bandage", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 2:
                                 this.addWorldItem("Pills", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 3:
                                 this.addWorldItem("AlcoholWipes", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 4:
                                 this.addWorldItem("Bandaid", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 5:
                                 this.addWorldItem("CottonBalls", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 6:
                                 this.addWorldItem("Disinfectant", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 7:
                                 this.addWorldItem("SutureNeedle", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 8:
                                 this.addWorldItem(
                                    "SutureNeedleHolder", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F
                                 );
                                 break;
                              case 9:
                                 this.addWorldItem("Tweezers", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F);
                                 break;
                              case 10:
                                 this.addWorldItem(
                                    "Gloves_Surgical", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F
                                 );
                                 break;
                              case 11:
                                 this.addWorldItem(
                                    "Hat_SurgicalMask_Blue", var6, Rand.Next(0.4F, 0.6F), Rand.Next(0.4F, 0.6F), var8.getSurfaceOffsetNoTable() / 96.0F
                                 );
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    bool roomValid(IsoGridSquare var1) {
      return var1.getRoom() != nullptr
         && ("hospitalroom" == var1.getRoom().getName()) || "clinic" == var1.getRoom().getName()) || "medical" == var1.getRoom().getName()));
   }

    bool isValid(BuildingDef var1, bool var2) {
      return var1.getRoom("medical") != nullptr || var1.getRoom("clinic") != nullptr || var2;
   }

    public RBClinic() {
      this.name = "Clinic (Vet, Doctor..)";
      this.setAlwaysDo(true);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
