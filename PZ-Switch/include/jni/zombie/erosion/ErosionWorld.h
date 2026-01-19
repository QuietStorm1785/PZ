#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionData/Chunk.h"
#include "zombie/erosion/ErosionData/Square.h"
#include "zombie/erosion/ErosionRegions/Region.h"
#include "zombie/erosion/categories/ErosionCategory.h"
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"

namespace zombie {
namespace erosion {


class ErosionWorld {
:
    bool init() {
      ErosionRegions.init();
    return true;
   }

    void validateSpawn(IsoGridSquare var1, Square var2, Chunk var3) {
    bool var4 = var1.Is(IsoFlagType.exterior);
    bool var5 = var1.Has(IsoObjectType.wall);
    IsoObject var6 = var1.getFloor();
    std::string var7 = var6 != nullptr && var6.getSprite() != nullptr ? var6.getSprite().getName() : nullptr;
      if (var7 == nullptr) {
         var2.doNothing = true;
      } else {
    bool var8 = false;

         for (int var9 = 0; var9 < ErosionRegions.regions.size(); var9++) {
    Region var10 = (Region)ErosionRegions.regions.get(var9);
    std::string var11 = var10.tileNameMatch;
            if ((var11 == nullptr || var7.startsWith(var11)) && (!var10.checkExterior || var10.isExterior == var4) && (!var10.hasWall || var10.hasWall == var5)) {
               for (int var12 = 0; var12 < var10.categories.size(); var12++) {
    ErosionCategory var13 = (ErosionCategory)var10.categories.get(var12);
    bool var14 = var13.replaceExistingObject(var1, var2, var3, var4, var5);
                  if (!var14) {
                     var14 = var13.validateSpawn(var1, var2, var3, var4, var5, false);
                  }

                  if (var14) {
                     var8 = true;
                     break;
                  }
               }
            }
         }

         if (!var8) {
            var2.doNothing = true;
         }
      }
   }

    void update(IsoGridSquare var1, Square var2, Chunk var3, int var4) {
      if (var2.regions != nullptr) {
         for (int var5 = 0; var5 < var2.regions.size(); var5++) {
    Data var6 = (Data)var2.regions.get(var5);
    ErosionCategory var7 = ErosionRegions.getCategory(var6.regionID, var6.categoryID);
    int var8 = var2.regions.size();
            var7.update(var1, var2, var6, var3, var4);
            if (var8 > var2.regions.size()) {
               var5--;
            }
         }
      }
   }
}
} // namespace erosion
} // namespace zombie
