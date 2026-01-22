#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/ErosionMain.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObjOverlaySprites {
public:
    const std::string sprite;

   public ErosionObjOverlaySprites$Sprite(std::string var1) {
      this.sprite = var1;
   }

    IsoSprite getSprite() {
      return this.sprite != nullptr ? ErosionMain.getInstance().getSpriteManager().getSprite(this.sprite) : nullptr;
   }

    IsoSpriteInstance getInstance() {
      return this.sprite != nullptr ? ErosionMain.getInstance().getSpriteManager().getSprite(this.sprite).newInstance() : nullptr;
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
