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

class FloorShaperDeDiamond {
public:
    float borderThicknessUp = 3.0F;
    float borderThicknessDown = 3.0F;
    float borderThicknessLR = 0.0F;
    float uvFraction = 0.01F;

   public FloorShaperDeDiamond$Settings$BorderSetting() {
   }

   public FloorShaperDeDiamond$Settings$BorderSetting(float var1, float var2, float var3, float var4) {
      this.borderThicknessUp = var1;
      this.borderThicknessDown = var2;
      this.borderThicknessLR = var3;
      this.uvFraction = var4;
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
