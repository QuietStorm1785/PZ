#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/erosion/ErosionData/Chunk.h"
#include "zombie/erosion/ErosionData/Square.h"
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include "zombie/erosion/categories/NaturePlants/CategoryData.h"
#include "zombie/erosion/categories/NaturePlants/PlantInit.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace erosion {
namespace categories {


class NaturePlants : public ErosionCategory {
public:
   private const int[][] soilRef = new int[][]{
      {17, 17, 17, 17, 17, 17, 17, 17, 17, 1, 2, 8, 8},
      {11, 12, 1, 2, 8, 1, 2, 8, 1, 2, 8, 1, 2, 8, 1, 2, 8},
      {11, 12, 11, 12, 11, 12, 11, 12, 15, 16, 18, 19},
      {22, 22, 22, 22, 22, 22, 22, 22, 22, 3, 4, 14},
      {15, 16, 3, 4, 14, 3, 4, 14, 3, 4, 14, 3, 4, 14},
      {11, 12, 15, 16, 15, 16, 15, 16, 15, 16, 21},
      {13, 13, 13, 13, 13, 13, 13, 13, 13, 5, 6, 24},
      {18, 19, 5, 6, 24, 5, 6, 24, 5, 6, 24, 5, 6, 24},
      {18, 19, 18, 19, 18, 19, 18, 19, 20, 21},
      {7, 7, 7, 7, 7, 7, 7, 7, 7, 9, 10, 23},
      {19, 20, 9, 10, 23, 9, 10, 23, 9, 10, 23, 9, 10, 23},
      {15, 16, 18, 19, 20, 19, 20, 19, 20}
   };
   private int[] spawnChance = new int[100];
   private std::vector<ErosionObj> objs = std::make_unique<std::vector<>>();
   private const PlantInit[] plants = new PlantInit[]{
    std::make_shared<PlantInit>("Butterfly Weed");
    std::make_shared<PlantInit>("Butterfly Weed");
    std::make_shared<PlantInit>("Swamp Sunflower");
    std::make_shared<PlantInit>("Swamp Sunflower");
    std::make_shared<PlantInit>("Purple Coneflower");
    std::make_shared<PlantInit>("Purple Coneflower");
    std::make_shared<PlantInit>("Joe-Pye Weed");
    std::make_shared<PlantInit>("Blazing Star");
    std::make_shared<PlantInit>("Wild Bergamot");
    std::make_shared<PlantInit>("Wild Bergamot");
    std::make_shared<PlantInit>("White Beard-tongue");
    std::make_shared<PlantInit>("White Beard-tongue");
    std::make_shared<PlantInit>();
    std::make_shared<PlantInit>("White Baneberry");
    std::make_shared<PlantInit>("Wild Columbine");
    std::make_shared<PlantInit>("Wild Columbine");
    std::make_shared<PlantInit>();
    std::make_shared<PlantInit>("Wild Ginger");
    std::make_shared<PlantInit>("Wild Ginger");
    std::make_shared<PlantInit>("Wild Geranium");
    std::make_shared<PlantInit>();
    std::make_shared<PlantInit>("Wild Blue);
    std::make_shared<PlantInit>("Polemonium Reptans");
    std::make_shared<PlantInit>();
   };

    bool replaceExistingObject(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5) {
    int var6 = var1.getObjects().size();

      for (int var7 = var6 - 1; var7 >= 1; var7--) {
    IsoObject var8 = (IsoObject)var1.getObjects().get(var7);
    IsoSprite var9 = var8.getSprite();
         if (var9 != nullptr && var9.getName() != nullptr) {
            if (var9.getName().startsWith("d_plants_1_")) {
    int var17 = int.parseInt(var9.getName().replace("d_plants_1_", ""));
    CategoryData var11 = (CategoryData)this.setCatModData(var2);
               var11.gameObj = var17 < 32 ? var17 % 8 : (var17 < 48 ? var17 % 8 + 8 : var17 % 8 + 16);
               var11.stage = 0;
               var11.spawnTime = 0;
               var1.RemoveTileObjectErosionNoRecalc(var8);
    return true;
            }

            if (!"vegetation_groundcover_01_16" == var9.getName()) && !"vegetation_groundcover_01_17" == var9.getName())) {
               if (!"vegetation_groundcover_01_18" == var9.getName())
                  && !"vegetation_groundcover_01_19" == var9.getName())
                  && !"vegetation_groundcover_01_20" == var9.getName())
                  && !"vegetation_groundcover_01_21" == var9.getName())
                  && !"vegetation_groundcover_01_22" == var9.getName())
                  && !"vegetation_groundcover_01_23" == var9.getName())) {
                  continue;
               }

    CategoryData var16 = (CategoryData)this.setCatModData(var2);
               var16.gameObj = Rand.Next(this.plants.length);
               var16.stage = 0;
               var16.spawnTime = 0;
               var1.RemoveTileObjectErosionNoRecalc(var8);

               while (--var7 > 0) {
                  var8 = (IsoObject)var1.getObjects().get(var7);
                  var9 = var8.getSprite();
                  if (var9 != nullptr && var9.getName() != nullptr && var9.getName().startsWith("vegetation_groundcover_01_")) {
                     var1.RemoveTileObjectErosionNoRecalc(var8);
                  }
               }

    return true;
            }

    CategoryData var10 = (CategoryData)this.setCatModData(var2);
            var10.gameObj = 21;
            var10.stage = 0;
            var10.spawnTime = 0;
            var1.RemoveTileObjectErosionNoRecalc(var8);

            while (--var7 > 0) {
               var8 = (IsoObject)var1.getObjects().get(var7);
               var9 = var8.getSprite();
               if (var9 != nullptr && var9.getName() != nullptr && var9.getName().startsWith("vegetation_groundcover_01_")) {
                  var1.RemoveTileObjectErosionNoRecalc(var8);
               }
            }

    return true;
         }
      }

    return false;
   }

    bool validateSpawn(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5, bool var6) {
      if (var1.getObjects().size() > (var5 ? 2 : 1)) {
    return false;
      } else if (var2.soil >= 0 && var2.soil < this.soilRef.length) {
         int[] var7 = this.soilRef[var2.soil];
    int var8 = var2.noiseMainInt;
         if (var2.rand(var1.x, var1.y, 101) < this.spawnChance[var8]) {
    CategoryData var9 = (CategoryData)this.setCatModData(var2);
            var9.gameObj = var7[var2.rand(var1.x, var1.y, var7.length)] - 1;
            var9.stage = 0;
            var9.spawnTime = 100 - var8;
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
    bool var8 = false;
    uint8_t var9 = 0;
    int var10 = this.currentSeason(var2.magicNum, var7);
    bool var11 = this.currentBloom(var2.magicNum, var7);
            this.updateObj(var2, var3, var1, var7, var8, var9, var10, var11);
         } else {
            this.clearCatModData(var2);
         }
      }
   }

    void init() {
      for (int var1 = 0; var1 < 100; var1++) {
         if (var1 >= 20 && var1 < 50) {
            this.spawnChance[var1] = (int)this.clerp((var1 - 20) / 30.0F, 0.0F, 8.0F);
         } else if (var1 >= 50 && var1 < 80) {
            this.spawnChance[var1] = (int)this.clerp((var1 - 50) / 30.0F, 8.0F, 0.0F);
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
    std::string var11 = "d_plants_1_";
    std::vector var2 = new std::vector();

      for (int var3 = 0; var3 <= 7; var3++) {
         var2.push_back(var11 + var3);
      }

    std::vector var12 = new std::vector();

      for (int var4 = 8; var4 <= 15; var4++) {
         var12.push_back(var11 + var4);
      }

    uint8_t var13 = 16;

      for (int var5 = 0; var5 < this.plants.length; var5++) {
         if (var5 >= 8) {
            var13 = 24;
         }

         if (var5 >= 16) {
            var13 = 32;
         }

    PlantInit var6 = this.plants[var5];
    ErosionObjSprites var7 = std::make_shared<ErosionObjSprites>(1, var6.name, false, var6.hasFlower, false);
         var7.setBase(0, var2, 1);
         var7.setBase(0, var12, 4);
         var7.setBase(0, var11 + (var13 + var5), 2);
         var7.setFlower(0, var11 + (var13 + var5 + 8));
    float var8 = var6.hasFlower ? var6.bloomstart : 0.0F;
    float var9 = var6.hasFlower ? var6.bloomend : 0.0F;
    ErosionObj var10 = std::make_shared<ErosionObj>(var7, 30, var8, var9, false);
         this.objs.push_back(var10);
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
