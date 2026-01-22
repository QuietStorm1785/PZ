#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObjOverlay {
public:
    const ErosionObjOverlaySprites sprites;
    std::string name;
    int stages;
    bool applyAlpha;
    int cycleTime;

    public ErosionObjOverlay(ErosionObjOverlaySprites var1, int var2, bool var3) {
      this.sprites = var1;
      this.name = var1.name;
      this.stages = var1.stages;
      this.applyAlpha = var3;
      this.cycleTime = var2;
   }

    int setOverlay(IsoObject var1, int var2, int var3, int var4, float var5) {
      if (var3 >= 0 && var3 < this.stages && var1 != nullptr) {
         if (var2 >= 0) {
            this.removeOverlay(var1, var2);
         }

    IsoSprite var6 = this.sprites.getSprite(var3, var4);
    IsoSpriteInstance var7 = var6.newInstance();
         if (var1.AttachedAnimSprite == nullptr) {
            var1.AttachedAnimSprite = std::make_unique<std::vector>();
         }

         var1.AttachedAnimSprite.push_back(var7);
         return var7.getID();
      } else {
         return -1;
      }
   }

    bool removeOverlay(IsoObject var1, int var2) {
      if (var1 == nullptr) {
    return false;
      } else {
    std::vector var3 = var1.AttachedAnimSprite;
         if (var3 != nullptr && !var3.empty()) {
            for (int var4 = 0; var4 < var1.AttachedAnimSprite.size(); var4++) {
               if (((IsoSpriteInstance)var1.AttachedAnimSprite.get(var4)).parentSprite.ID == var2) {
                  var1.AttachedAnimSprite.remove(var4--);
               }
            }

            for (int var5 = var3.size() - 1; var5 >= 0; var5--) {
               if (((IsoSpriteInstance)var3.get(var5)).getID() == var2) {
                  var3.remove(var5);
    return true;
               }
            }

    return false;
         } else {
    return false;
         }
      }
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
