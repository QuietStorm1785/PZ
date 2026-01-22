#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionData/Chunk.h"
#include "zombie/erosion/ErosionData/Square.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include "zombie/erosion/categories/Flowerbed/CategoryData.h"
#include "zombie/erosion/obj/ErosionObj.h"
#include "zombie/erosion/obj/ErosionObjSprites.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace erosion {
namespace categories {


class Flowerbed : public ErosionCategory {
public:
   private const int[] tileID = new int[]{16, 17, 18, 19, 20, 21, 22, 23, 28, 29, 30, 31};
   private const std::vector<ErosionObj> objs = std::make_unique<std::vector<>>();

    bool replaceExistingObject(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5) {
    int var6 = var1.getObjects().size();

      for (int var7 = var6 - 1; var7 >= 0; var7--) {
    IsoSprite var8 = ((IsoObject)var1.getObjects().get(var7)).getSprite();
         if (var8 != nullptr && var8.getName() != nullptr) {
            if (var8.getName().startsWith("f_flowerbed_1")) {
    int var9 = int.parseInt(var8.getName().replace("f_flowerbed_1_", ""));
               if (var9 <= 23) {
                  if (var9 >= 12) {
                     var9 -= 12;
                  }

    CategoryData var14 = (CategoryData)this.setCatModData(var2);
                  var14.hasSpawned = true;
                  var14.gameObj = var9;
                  var14.dispSeason = -1;
    ErosionObj var15 = this.objs.get(var14.gameObj);
                  ((IsoObject)var1.getObjects().get(var7)).setName(var15.name);
    return true;
               }
            }

            if (var8.getName().startsWith("vegetation_ornamental_01")) {
    int var13 = int.parseInt(var8.getName().replace("vegetation_ornamental_01_", ""));

               for (int var10 = 0; var10 < this.tileID.length; var10++) {
                  if (this.tileID[var10] == var13) {
    CategoryData var11 = (CategoryData)this.setCatModData(var2);
                     var11.hasSpawned = true;
                     var11.gameObj = var10;
                     var11.dispSeason = -1;
    ErosionObj var12 = this.objs.get(var11.gameObj);
                     ((IsoObject)var1.getObjects().get(var7)).setName(var12.name);
    return true;
                  }
               }
            }
         }
      }

    return false;
   }

    bool validateSpawn(IsoGridSquare var1, Square var2, Chunk var3, bool var4, bool var5, bool var6) {
    return false;
   }

    void update(IsoGridSquare var1, Square var2, Data var3, Chunk var4, int var5) {
    CategoryData var6 = (CategoryData)var3;
      if (!var6.doNothing) {
         if (var6.gameObj >= 0 && var6.gameObj < this.objs.size()) {
    ErosionObj var7 = this.objs.get(var6.gameObj);
    bool var8 = false;
    uint8_t var9 = 0;
    int var10 = ErosionMain.getInstance().getSeasons().getSeason();
    bool var11 = false;
            if (var10 == 5) {
    IsoObject var12 = var7.getObject(var1, false);
               if (var12 != nullptr) {
                  var12.setSprite(ErosionMain.getInstance().getSpriteManager().getSprite("blends_natural_01_64"));
                  var12.setName(nullptr);
               }

               this.clearCatModData(var2);
            } else {
               this.updateObj(var2, var3, var1, var7, var8, var9, var10, var11);
            }
         } else {
            this.clearCatModData(var2);
         }
      }
   }

    void init() {
    std::string var1 = "vegetation_ornamental_01_";

      for (int var2 = 0; var2 < this.tileID.length; var2++) {
    ErosionObjSprites var3 = std::make_shared<ErosionObjSprites>(1, "Flowerbed", false, false, false);
         var3.setBase(0, var1 + this.tileID[var2], 1);
         var3.setBase(0, var1 + this.tileID[var2], 2);
         var3.setBase(0, var1 + (this.tileID[var2] + 16), 4);
    ErosionObj var4 = std::make_shared<ErosionObj>(var3, 30, 0.0F, 0.0F, false);
         this.objs.push_back(var4);
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
