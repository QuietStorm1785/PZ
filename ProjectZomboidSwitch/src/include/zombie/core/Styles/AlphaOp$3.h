#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/ReadableColor.h"

namespace zombie {
namespace core {
namespace Styles {


enum class AlphaOp {
    int calc(ReadableColor var1, int var2) {
    float var3 = var1.getAlpha() * var2 * 0.003921569F;
    float var4 = var3 * 0.003921569F;
      return (int)(var1.getRed() * var4) << 0 | (int)(var1.getGreen() * var4) << 8 | (int)(var1.getBlue() * var4) << 16;
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
