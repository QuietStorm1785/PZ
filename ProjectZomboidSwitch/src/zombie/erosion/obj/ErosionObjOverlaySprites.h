#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/obj/ErosionObjOverlaySprites/Sprite.h"
#include "zombie/erosion/obj/ErosionObjOverlaySprites/Stage.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObjOverlaySprites {
public:
    std::string name;
    int stages;
   private Stage[] sprites;

    public ErosionObjOverlaySprites(int var1, const std::string& var2) {
      this.name = var2;
      this.stages = var1;
      this.sprites = new Stage[this.stages];

      for (int var3 = 0; var3 < this.stages; var3++) {
         this.sprites[var3] = std::make_unique<Stage>();
      }
   }

    IsoSprite getSprite(int var1, int var2) {
      return this.sprites[var1].seasons[var2].getSprite();
   }

    IsoSpriteInstance getSpriteInstance(int var1, int var2) {
      return this.sprites[var1].seasons[var2].getInstance();
   }

    void setSprite(int var1, const std::string& var2, int var3) {
      this.sprites[var1].seasons[var3] = std::make_shared<Sprite>(var2);
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
