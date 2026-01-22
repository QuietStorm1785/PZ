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
      return var1.getRed() << 0 | var1.getGreen() << 8 | var1.getBlue() << 16 | var1.getAlpha() << 24;
   }
}
} // namespace Styles
} // namespace core
} // namespace zombie
