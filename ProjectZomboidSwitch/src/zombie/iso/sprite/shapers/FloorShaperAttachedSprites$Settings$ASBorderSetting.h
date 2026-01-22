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

class FloorShaperAttachedSprites {
public:
    float borderThicknessUp;
    float borderThicknessDown;
    float borderThicknessLR;
    float uvFraction;

   public FloorShaperAttachedSprites$Settings$ASBorderSetting() {
   }

   public FloorShaperAttachedSprites$Settings$ASBorderSetting(float var1, float var2, float var3, float var4) {
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
