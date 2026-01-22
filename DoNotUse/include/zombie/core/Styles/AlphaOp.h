#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/ReadableColor.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace Styles {


enum class AlphaOp {
   PREMULTIPLY,
   KEEP,
   ZERO;

    static const float PREMULT_ALPHA = 0.003921569F;

    void op(ReadableColor var1, int var2, FloatBuffer var3) {
      var3.put(float.intBitsToFloat(this.calc(var1, var2)));
   }

    void op(int var1, int var2, FloatBuffer var3) {
      var3.put(float.intBitsToFloat(var1));
   }

   protected abstract int calc(ReadableColor var1, int var2);
}
} // namespace Styles
} // namespace core
} // namespace zombie
