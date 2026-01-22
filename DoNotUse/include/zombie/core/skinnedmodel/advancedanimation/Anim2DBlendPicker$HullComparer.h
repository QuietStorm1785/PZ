#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class Anim2DBlendPicker {
public:
    int centerX;
    int centerY;

   public Anim2DBlendPicker$HullComparer(float var1, float var2) {
      this.centerX = (int)(var1 * 1000.0F);
      this.centerY = (int)(var2 * 1000.0F);
   }

    bool isLessThan(Anim2DBlend var1, Anim2DBlend var2) {
    int var3 = (int)(var1.m_XPos * 1000.0F);
    int var4 = (int)(var1.m_YPos * 1000.0F);
    int var5 = (int)(var2.m_XPos * 1000.0F);
    int var6 = (int)(var2.m_YPos * 1000.0F);
    int var7 = var3 - this.centerX;
    int var8 = var4 - this.centerY;
    int var9 = var5 - this.centerX;
    int var10 = var6 - this.centerY;
      if (var8 == 0 && var7 > 0) {
    return true;
      } else if (var10 == 0 && var9 > 0) {
    return false;
      } else if (var8 > 0 && var10 < 0) {
    return true;
      } else if (var8 < 0 && var10 > 0) {
    return false;
      } else {
    int var11 = var7 * var10 - var8 * var9;
         return var11 > 0;
      }
   }

    int compare(Anim2DBlend var1, Anim2DBlend var2) {
      if (this.isLessThan(var1, var2)) {
         return -1;
      } else {
         return this.isLessThan(var2, var1) ? 1 : 0;
      }
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
