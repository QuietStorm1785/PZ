#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionData/Chunk.h"
#include "zombie/erosion/ErosionData/Square.h"
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include "zombie/erosion/categories/WallCracks/CategoryData.h"
#include "zombie/erosion/obj/ErosionObjOverlay.h"
#include "zombie/erosion/obj/ErosionObjOverlaySprites.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace erosion {
namespace categories {


class WallCracks : public ErosionCategory {
public:
   private std::vector<ErosionObjOverlay> objs = std::make_unique<std::vector<>>();
    static const int DIRNW = 0;
    static const int DIRN = 1;
    static const int DIRW = 2;
   private std::vector<std::vector<int>> objsRef = std::make_unique<std::vector<>>();
   private std::vector<std::vector<int>> botRef = std::make_unique<std::vector<>>();
   private std::vector<std::vector<int>> topRef = std::make_unique<std::vector<>>();
   private int[] spawnChance = new int[100];

    bool replaceExistingObject(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5) {
    return false;
   }

    bool validateSpawn(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5, bool var6) {
      if (!var4) {
    return false;
      } else {
    int var7 = var2.noiseMainInt;
    int var8 = this.spawnChance[var7];
         if (var8 == 0) {
    return false;
         } else if (var2.rand(var1.x, var1.y, 101) >= var8) {
    return false;
         } else {
    uint8_t var9 = -1;
    IsoObject var11 = this.validWall(var1, true, false);
            if (var11 != nullptr) {
    std::string var10 = var11.getSprite().getName();
               if (var10 != nullptr && var10.startsWith("fencing")) {
                  var11 = nullptr;
               }
            }

    IsoObject var12 = this.validWall(var1, false, false);
            if (var12 != nullptr) {
    std::string var20 = var12.getSprite().getName();
               if (var20 != nullptr && var20.startsWith("fencing")) {
                  var12 = nullptr;
               }
            }

            if (var11 != nullptr && var12 != nullptr) {
               var9 = 0;
            } else if (var11 != nullptr) {
               var9 = 1;
            } else {
               if (var12 == nullptr) {
    return false;
               }

               var9 = 2;
            }

    bool var13 = var7 < 35 && var2.magicNum > 0.3F;
    CategoryData var14 = (CategoryData)this.setCatModData(var2);
            var14.gameObj = this.objsRef.get(var9).get(var2.rand(var1.x, var1.y, this.objsRef.get(var9).size()));
            var14.alpha = 0.0F;
            var14.spawnTime = var7;
            if (var13) {
    IsoGridSquare var15 = IsoWorld.instance.CurrentCell.getGridSquare(var1.getX(), var1.getY(), var1.getZ() + 1);
               if (var15 != nullptr) {
    IsoObject var16 = this.validWall(var15, var9 == 1, false);
                  if (var16 != nullptr) {
    int var17 = var2.rand(var1.x, var1.y, this.botRef.get(var9).size());
                     var14.gameObj = this.botRef.get(var9).get(var17);
    CategoryData var18 = std::make_shared<CategoryData>();
                     var18.gameObj = this.topRef.get(var9).get(var17);
                     var18.alpha = 0.0F;
                     var18.spawnTime = var14.spawnTime;
                     var14.hasTop = var18;
                  }
               }
            }

    return true;
         }
      }
   }

    void update(IsoGridSquare var1, Square var2, Data var3, Chunk var4, int var5) {
    CategoryData var6 = (CategoryData)var3;
      if (var5 >= var6.spawnTime && !var6.doNothing) {
         if (var6.gameObj >= 0 && var6.gameObj < this.objs.size()) {
    ErosionObjOverlay var7 = this.objs.get(var6.gameObj);
    float var8 = var6.alpha;
    float var9 = (var5 - var6.spawnTime) / 100.0F;
            if (var9 > 1.0F) {
               var9 = 1.0F;
            }

            if (var9 < 0.0F) {
               var9 = 0.0F;
            }

            if (var9 != var8) {
    IsoObject var10 = nullptr;
    IsoObject var11 = this.validWall(var1, true, false);
    IsoObject var12 = this.validWall(var1, false, false);
               if (var11 != nullptr && var12 != nullptr) {
                  var10 = var11;
               } else if (var11 != nullptr) {
                  var10 = var11;
               } else if (var12 != nullptr) {
                  var10 = var12;
               }

               if (var10 != nullptr) {
    int var13 = var6.curID;
    uint8_t var14 = 0;
    int var15 = var7.setOverlay(var10, var13, var14, 0, var9);
                  if (var15 >= 0) {
                     var6.alpha = var9;
                     var6.curID = var15;
                  }
               } else {
                  var6.doNothing = true;
               }

               if (var6.hasTop != nullptr) {
    IsoGridSquare var16 = IsoWorld.instance.CurrentCell.getGridSquare(var1.getX(), var1.getY(), var1.getZ() + 1);
                  if (var16 != nullptr) {
                     this.update(var16, var2, var6.hasTop, var4, var5);
                  }
               }
            }
         } else {
            var6.doNothing = true;
         }
      }
   }

    void init() {
      for (int var1 = 0; var1 < 100; var1++) {
         this.spawnChance[var1] = var1 <= 50 ? 100 : 0;
      }

    std::string var7 = "d_wallcracks_1_";
      int[] var2 = new int[]{2, 2, 2, 1, 1, 1, 0, 0, 0};

      for (int var3 = 0; var3 < 3; var3++) {
         this.objsRef.push_back(std::make_unique<std::vector<>>());
         this.topRef.push_back(std::make_unique<std::vector<>>());
         this.botRef.push_back(std::make_unique<std::vector<>>());
      }

      for (int var8 = 0; var8 < var2.length; var8++) {
         for (int var4 = 0; var4 <= 7; var4++) {
    int var5 = var4 * 9 + var8;
    ErosionObjOverlaySprites var6 = std::make_shared<ErosionObjOverlaySprites>(1, "WallCracks");
            var6.setSprite(0, var7 + var5, 0);
            this.objs.push_back(std::make_shared<ErosionObjOverlay>(var6, 60, true));
            this.objsRef.get(var2[var8]).push_back(this.objs.size() - 1);
            if (var4 == 0) {
               this.botRef.get(var2[var8]).push_back(this.objs.size() - 1);
            } else if (var4 == 1) {
               this.topRef.get(var2[var8]).push_back(this.objs.size() - 1);
            }
         }
      }
   }

    Data allocData() {
      return std::make_unique<CategoryData>();
   }

    void getObjectNames(std::vector<std::string> var1) {
      for (int var2 = 0; var2 < this.objs.size(); var2++) {
         if (this.objs.get(var2).name != nullptr && !var1.contains(this.objs.get(var2).name)) {
            var1.push_back(this.objs.get(var2).name);
         }
      }
   }
}
} // namespace categories
} // namespace erosion
} // namespace zombie
