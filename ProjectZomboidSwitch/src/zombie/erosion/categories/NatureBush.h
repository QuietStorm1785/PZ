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
#include "zombie/erosion/categories/NatureBush/BushInit.h"
#include "zombie/erosion/categories/NatureBush/CategoryData.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
#include "zombie/erosion/season/ErosionIceQueen.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace erosion {
namespace categories {


class NatureBush : public ErosionCategory {
public:
   private const int[][] soilRef = new int[][]{
      {11, 11, 12, 13},
      {5, 5, 7, 8, 11, 11, 12, 13, 11, 11, 12, 13},
      {5, 5, 7, 8, 5, 5, 7, 8, 11, 11, 12, 13},
      {1, 1, 4, 5},
      {5, 5, 7, 8, 1, 1, 4, 5, 1, 1, 4, 5},
      {5, 5, 7, 8, 5, 5, 7, 8, 1, 1, 4, 5},
      {9, 10, 14, 15},
      {5, 5, 7, 8, 9, 10, 14, 15, 9, 10, 14, 15},
      {5, 5, 7, 8, 5, 5, 7, 8, 9, 10, 14, 15},
      {2, 3, 16, 16},
      {5, 5, 7, 8, 2, 3, 16, 16, 2, 3, 16, 16},
      {5, 5, 7, 8, 5, 5, 7, 8, 2, 3, 16, 16}
   };
   private std::vector<ErosionObj> objs = std::make_unique<std::vector<>>();
   private int[] spawnChance = new int[100];
   private BushInit[] bush = new BushInit[]{
    std::make_shared<BushInit>();
    std::make_shared<BushInit>();
    std::make_shared<BushInit>();
    std::make_shared<BushInit>();
    std::make_shared<BushInit>();
    std::make_shared<BushInit>("Piedmont azalea");
    std::make_shared<BushInit>("Piedmont azalea");
    std::make_shared<BushInit>("Arrowwood viburnum");
    std::make_shared<BushInit>("Red chokeberry");
    std::make_shared<BushInit>("Red chokeberry");
    std::make_shared<BushInit>();
    std::make_shared<BushInit>("New jersey);
    std::make_shared<BushInit>("New jersey);
    std::make_shared<BushInit>("Wild hydrangea");
    std::make_shared<BushInit>("Wild hydrangea");
    std::make_shared<BushInit>("Shrubby St.);
   };

    bool replaceExistingObject(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5) {
    int var6 = var1.getObjects().size();
    bool var7 = false;

      for (int var8 = var6 - 1; var8 >= 1; var8--) {
    IsoObject var9 = (IsoObject)var1.getObjects().get(var8);
    IsoSprite var10 = var9.getSprite();
         if (var10 != nullptr && var10.getName() != nullptr) {
            if (var10.getName().startsWith("vegetation_foliage")) {
    int var11 = var2.soil;
               if (var11 < 0 || var11 >= this.soilRef.length) {
                  var11 = var2.rand(var1.x, var1.y, this.soilRef.length);
               }

               int[] var12 = this.soilRef[var11];
    int var13 = var2.noiseMainInt;
    CategoryData var14 = (CategoryData)this.setCatModData(var2);
               var14.gameObj = var12[var2.rand(var1.x, var1.y, var12.length)] - 1;
               var14.maxStage = (int)Math.floor(var13 / 60.0F);
               var14.stage = var14.maxStage;
               var14.spawnTime = 0;
               var1.RemoveTileObject(var9);
               var7 = true;
            }

            if (var10.getName().startsWith("f_bushes_1_")) {
    int var15 = int.parseInt(var10.getName().replace("f_bushes_1_", ""));
    CategoryData var16 = (CategoryData)this.setCatModData(var2);
               var16.gameObj = var15 % 16;
               var16.maxStage = 1;
               var16.stage = var16.maxStage;
               var16.spawnTime = 0;
               var1.RemoveTileObject(var9);
               var7 = true;
            }
         }
      }

    return var7;
   }

    bool validateSpawn(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5, bool var6) {
      if (var1.getObjects().size() > (var5 ? 2 : 1)) {
    return false;
      } else if (var2.soil >= 0 && var2.soil < this.soilRef.length) {
         int[] var7 = this.soilRef[var2.soil];
    int var8 = var2.noiseMainInt;
    int var9 = var2.rand(var1.x, var1.y, 101);
         if (var9 < this.spawnChance[var8]) {
    CategoryData var10 = (CategoryData)this.setCatModData(var2);
            var10.gameObj = var7[var2.rand(var1.x, var1.y, var7.length)] - 1;
            var10.maxStage = (int)Math.floor(var8 / 60.0F);
            var10.stage = 0;
            var10.spawnTime = 100 - var8;
    return true;
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    void update(IsoGridSquare var1, Square var2, Data var3, Chunk var4, int var5) {
    CategoryData var6 = (CategoryData)var3;
      if (var5 >= var6.spawnTime && !var6.doNothing) {
         if (var6.gameObj >= 0 && var6.gameObj < this.objs.size()) {
    ErosionObj var7 = this.objs.get(var6.gameObj);
    int var8 = var6.maxStage;
    int var9 = (int)Math.floor((var5 - var6.spawnTime) / (var7.cycleTime / (var8 + 1.0F)));
            if (var9 < var6.stage) {
               var9 = var6.stage;
            }

            if (var9 > var8) {
               var9 = var8;
            }

    int var10 = this.currentSeason(var2.magicNum, var7);
    bool var11 = this.currentBloom(var2.magicNum, var7);
    bool var12 = false;
            this.updateObj(var2, var3, var1, var7, var12, var9, var10, var11);
         } else {
            var6.doNothing = true;
         }
      }
   }

    void init() {
      for (int var1 = 0; var1 < 100; var1++) {
         if (var1 >= 45 && var1 < 60) {
            this.spawnChance[var1] = (int)this.clerp((var1 - 45) / 15.0F, 0.0F, 20.0F);
         }

         if (var1 >= 60 && var1 < 90) {
            this.spawnChance[var1] = (int)this.clerp((var1 - 60) / 30.0F, 20.0F, 0.0F);
         }
      }

      this.seasonDisp[5].season1 = 0;
      this.seasonDisp[5].season2 = 0;
      this.seasonDisp[5].split = false;
      this.seasonDisp[1].season1 = 1;
      this.seasonDisp[1].season2 = 0;
      this.seasonDisp[1].split = false;
      this.seasonDisp[2].season1 = 2;
      this.seasonDisp[2].season2 = 2;
      this.seasonDisp[2].split = true;
      this.seasonDisp[4].season1 = 4;
      this.seasonDisp[4].season2 = 0;
      this.seasonDisp[4].split = true;
    ErosionIceQueen var17 = ErosionIceQueen.instance;
    std::string var2 = "f_bushes_1_";

      for (int var3 = 1; var3 <= this.bush.length; var3++) {
    int var4 = var3 - 1;
    int var5 = var4 - (int)Math.floor(var4 / 8.0F) * 8;
    BushInit var6 = this.bush[var4];
    ErosionObjSprites var7 = std::make_shared<ErosionObjSprites>(2, var6.name, true, var6.hasFlower, true);
    int var8 = 0 + var5;
    int var9 = var8 + 16;
    int var10 = var9 + 16;
    int var11 = var10 + 16;
    int var12 = 64 + var4;
    int var13 = var12 + 16;
         var7.setBase(0, var2 + var8, 0);
         var7.setBase(1, var2 + (var8 + 8), 0);
         var17.addSprite(var2 + var8, var2 + var9);
         var17.addSprite(var2 + (var8 + 8), var2 + (var9 + 8));
         var7.setChildSprite(0, var2 + var10, 1);
         var7.setChildSprite(1, var2 + (var10 + 8), 1);
         var7.setChildSprite(0, var2 + var11, 4);
         var7.setChildSprite(1, var2 + (var11 + 8), 4);
         var7.setChildSprite(0, var2 + var12, 2);
         var7.setChildSprite(1, var2 + (var12 + 32), 2);
         if (var6.hasFlower) {
            var7.setFlower(0, var2 + var13);
            var7.setFlower(1, var2 + (var13 + 32));
         }

    float var14 = var6.hasFlower ? var6.bloomstart : 0.0F;
    float var15 = var6.hasFlower ? var6.bloomend : 0.0F;
    ErosionObj var16 = std::make_shared<ErosionObj>(var7, 60, var14, var15, true);
         this.objs.push_back(var16);
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
