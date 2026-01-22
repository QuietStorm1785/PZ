#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace sprite {

class IsoSpriteGrid {
public:
   private IsoSprite[] sprites;
    int width;
    int height;

    public IsoSpriteGrid(int var1, int var2) {
      this.sprites = new IsoSprite[var1 * var2];
      this.width = var1;
      this.height = var2;
   }

    IsoSprite getAnchorSprite() {
      return this.sprites.length > 0 ? this.sprites[0] : nullptr;
   }

    IsoSprite getSprite(int var1, int var2) {
      return this.getSpriteFromIndex(var2 * this.width + var1);
   }

    void setSprite(int var1, int var2, IsoSprite var3) {
      this.sprites[var2 * this.width + var1] = var3;
   }

    int getSpriteIndex(IsoSprite var1) {
      for (int var3 = 0; var3 < this.sprites.length; var3++) {
    IsoSprite var2 = this.sprites[var3];
         if (var2 != nullptr && var2 == var1) {
    return var3;
         }
      }

      return -1;
   }

    int getSpriteGridPosX(IsoSprite var1) {
    int var2 = this.getSpriteIndex(var1);
      return var2 >= 0 ? var2 % this.width : -1;
   }

    int getSpriteGridPosY(IsoSprite var1) {
    int var2 = this.getSpriteIndex(var1);
      return var2 >= 0 ? var2 / this.width : -1;
   }

    IsoSprite getSpriteFromIndex(int var1) {
      return var1 >= 0 && var1 < this.sprites.length ? this.sprites[var1] : nullptr;
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }

    bool validate() {
      for (int var1 = 0; var1 < this.sprites.length; var1++) {
         if (this.sprites[var1] == nullptr) {
    return false;
         }
      }

    return true;
   }

    int getSpriteCount() {
      return this.sprites.length;
   }

   public IsoSprite[] getSprites() {
      return this.sprites;
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
