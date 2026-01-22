#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace erosion {
namespace season {


class ErosionIceQueen {
public:
    IsoSprite sprite;
    std::string normal;
    std::string winter;

   public ErosionIceQueen$Sprite(IsoSprite var1, std::string var2, std::string var3) {
      this.sprite = var1;
      this.normal = var2;
      this.winter = var3;
   }
}
} // namespace season
} // namespace erosion
} // namespace zombie
