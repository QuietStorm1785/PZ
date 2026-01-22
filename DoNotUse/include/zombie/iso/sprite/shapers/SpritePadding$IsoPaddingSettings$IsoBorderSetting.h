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
namespace shapers {

class SpritePadding {
public:
    float borderThickness;
    float uvFraction;

   public SpritePadding$IsoPaddingSettings$IsoBorderSetting() {
   }

   public SpritePadding$IsoPaddingSettings$IsoBorderSetting(float var1, float var2) {
      this.borderThickness = var1;
      this.uvFraction = var2;
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
