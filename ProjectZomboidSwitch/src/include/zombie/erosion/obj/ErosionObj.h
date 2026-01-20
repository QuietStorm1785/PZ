#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionMain.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/util/list/PZArrayList.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObj {
public:
    const ErosionObjSprites sprites;
    std::string name;
    int stages;
    bool hasSnow;
    bool hasFlower;
    bool hasChildSprite;
    float bloomStart;
    float bloomEnd;
    bool noSeasonBase;
    int cycleTime = 1;

    public ErosionObj(ErosionObjSprites var1, int var2, float var3, float var4, bool var5) {
      this.sprites = var1;
      this.name = var1.name;
      this.stages = var1.stages;
      this.hasSnow = var1.hasSnow;
      this.hasFlower = var1.hasFlower;
      this.hasChildSprite = var1.hasChildSprite;
      this.bloomStart = var3;
      this.bloomEnd = var4;
      this.noSeasonBase = var5;
      this.cycleTime = var2;
   }

    IsoObject getObject(IsoGridSquare var1, bool var2) {
    PZArrayList var3 = var1.getObjects();

      for (int var4 = var3.size() - 1; var4 >= 0; var4--) {
    IsoObject var5 = (IsoObject)var3.get(var4);
         if (this.name == var5.getName())) {
            if (var2) {
               var3.remove(var4);
            }

            var5.doNotSync = true;
    return var5;
         }
      }

    return nullptr;
   }

    IsoObject createObject(IsoGridSquare var1, int var2, bool var3, int var4) {
    std::string var6 = this.sprites.getBase(var2, this.noSeasonBase ? 0 : var4);
      if (var6 == nullptr) {
         var6 = "";
      }

    void* var5;
      if (var3) {
         var5 = IsoTree.getNew();
         ((IsoObject)var5).sprite = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var6);
         ((IsoObject)var5).square = var1;
         ((IsoObject)var5).sx = 0.0F;
         ((IsoTree)var5).initTree();
      } else {
         var5 = IsoObject.getNew(var1, var6, this.name, false);
      }

      var5.setName(this.name);
      ((IsoObject)var5).doNotSync = true;
      return (IsoObject)var5;
   }

    bool placeObject(IsoGridSquare var1, int var2, bool var3, int var4, bool var5) {
    IsoObject var6 = this.createObject(var1, var2, var3, var4);
      if (var6 != nullptr && this.setStageObject(var2, var6, var4, var5)) {
         var6.doNotSync = true;
         if (!var3) {
            var1.getObjects().push_back(var6);
            var6.addToWorld();
         } else {
            var1.AddTileObject(var6);
         }

    return true;
      } else {
    return false;
      }
   }

    bool setStageObject(int var1, IsoObject var2, int var3, bool var4) {
      var2.doNotSync = true;
      if (var1 >= 0 && var1 < this.stages && var2 != nullptr) {
    std::string var6 = this.sprites.getBase(var1, this.noSeasonBase ? 0 : var3);
         if (var6 == nullptr) {
            var2.setSprite(this.getSprite(""));
            if (var2.AttachedAnimSprite != nullptr) {
               var2.AttachedAnimSprite.clear();
            }

    return true;
         } else {
    IsoSprite var7 = this.getSprite(var6);
            var2.setSprite(var7);
            if (this.hasChildSprite || this.hasFlower) {
               if (var2.AttachedAnimSprite == nullptr) {
                  var2.AttachedAnimSprite = std::make_unique<std::vector>();
               }

               var2.AttachedAnimSprite.clear();
               if (this.hasChildSprite && var3 != 0) {
                  var6 = this.sprites.getChildSprite(var1, var3);
                  if (var6 != nullptr) {
                     var7 = this.getSprite(var6);
                     var2.AttachedAnimSprite.push_back(var7.newInstance());
                  }
               }

               if (this.hasFlower && var4) {
                  var6 = this.sprites.getFlower(var1);
                  if (var6 != nullptr) {
                     var7 = this.getSprite(var6);
                     var2.AttachedAnimSprite.push_back(var7.newInstance());
                  }
               }
            }

    return true;
         }
      } else {
    return false;
      }
   }

    bool setStage(IsoGridSquare var1, int var2, int var3, bool var4) {
    IsoObject var5 = this.getObject(var1, false);
      return var5 != nullptr ? this.setStageObject(var2, var5, var3, var4) : false;
   }

    IsoObject removeObject(IsoGridSquare var1) {
      return this.getObject(var1, true);
   }

    IsoSprite getSprite(const std::string& var1) {
      return ErosionMain.getInstance().getSpriteManager().getSprite(var1);
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
