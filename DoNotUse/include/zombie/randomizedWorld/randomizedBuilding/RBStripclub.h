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
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBStripclub : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
      var1.setHasBeenVisited(true);
      var1.setAllExplored(true);
    IsoCell var2 = IsoWorld.instance.CurrentCell;
    bool var3 = Rand.NextBool(20);
    std::vector var4 = new std::vector();

      for (int var5 = var1.x - 1; var5 < var1.x2 + 1; var5++) {
         for (int var6 = var1.y - 1; var6 < var1.y2 + 1; var6++) {
            for (int var7 = 0; var7 < 8; var7++) {
    IsoGridSquare var8 = var2.getGridSquare(var5, var6, var7);
               if (var8 != nullptr) {
                  for (int var9 = 0; var9 < var8.getObjects().size(); var9++) {
    IsoObject var10 = (IsoObject)var8.getObjects().get(var9);
                     if (Rand.NextBool(2) && "location_restaurant_pizzawhirled_01_16" == var10.getSprite().getName())) {
    int var11 = Rand.Next(1, 4);

                        for (int var12 = 0; var12 < var11; var12++) {
                           var8.AddWorldInventoryItem("Money", Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                        }

    int var17 = Rand.Next(1, 4);

                        for (int var13 = 0; var13 < var17; var13++) {
    int var14 = Rand.Next(1, 7);

                           while (var4.contains(var14)) {
                              var14 = Rand.Next(1, 7);
                           }

                           switch (var14) {
                              case 1:
                                 var8.AddWorldInventoryItem(var3 ? "Trousers" : "TightsFishnet_Ground", Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                                 var4.push_back(1);
                                 break;
                              case 2:
                                 var8.AddWorldInventoryItem("Vest_DefaultTEXTURE_TINT", Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                                 var4.push_back(2);
                                 break;
                              case 3:
                                 var8.AddWorldInventoryItem(var3 ? "Jacket_Fireman" : "BunnySuitBlack", Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                                 var4.push_back(3);
                                 break;
                              case 4:
                                 var8.AddWorldInventoryItem(var3 ? "Hat_Cowboy" : "Garter", Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                                 var4.push_back(4);
                                 break;
                              case 5:
                                 if (!var3) {
                                    var8.AddWorldInventoryItem("StockingsBlack", Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                                 }

                                 var4.push_back(5);
                           }
                        }
                     }

                     if ("furniture_tables_high_01_16" == var10.getSprite().getName())
                        || "furniture_tables_high_01_17" == var10.getSprite().getName())
                        || "furniture_tables_high_01_18" == var10.getSprite().getName())) {
    int var16 = Rand.Next(1, 4);

                        for (int var18 = 0; var18 < var16; var18++) {
                           var8.AddWorldInventoryItem("Money", Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), var10.getSurfaceOffsetNoTable() / 96.0F);
                        }

                        if (Rand.NextBool(3)) {
                           this.addWorldItem("Cigarettes", var8, var10);
                           if (Rand.NextBool(2)) {
                              this.addWorldItem("Lighter", var8, var10);
                           }
                        }

    int var19 = Rand.Next(7);
                        switch (var19) {
                           case 0:
                              var8.AddWorldInventoryItem("WhiskeyFull", Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), var10.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 1:
                              var8.AddWorldInventoryItem("Wine", Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), var10.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 2:
                              var8.AddWorldInventoryItem("Wine2", Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), var10.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 3:
                              var8.AddWorldInventoryItem("BeerCan", Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), var10.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 4:
                              var8.AddWorldInventoryItem("BeerBottle", Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), var10.getSurfaceOffsetNoTable() / 96.0F);
                        }
                     }
                  }
               }
            }
         }
      }

    RoomDef var15 = var1.getRoom("stripclub");
      if (var3) {
         this.addZombies(var1, Rand.Next(2, 4), "WaiterStripper", 0, var15);
         this.addZombies(var1, 1, "PoliceStripper", 0, var15);
         this.addZombies(var1, 1, "FiremanStripper", 0, var15);
         this.addZombies(var1, 1, "CowboyStripper", 0, var15);
         this.addZombies(var1, Rand.Next(9, 15), nullptr, 100, var15);
      } else {
         this.addZombies(var1, Rand.Next(2, 4), "WaiterStripper", 100, var15);
         this.addZombies(var1, Rand.Next(2, 5), "StripperNaked", 100, var15);
         this.addZombies(var1, Rand.Next(2, 5), "StripperBlack", 100, var15);
         this.addZombies(var1, Rand.Next(2, 5), "StripperWhite", 100, var15);
         this.addZombies(var1, Rand.Next(9, 15), nullptr, 0, var15);
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      return var1.getRoom("stripclub") != nullptr || var2;
   }

    public RBStripclub() {
      this.name = "Stripclub";
      this.setAlwaysDo(true);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
