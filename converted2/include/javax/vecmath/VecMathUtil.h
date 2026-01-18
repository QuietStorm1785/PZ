#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VecMathUtil {
public:
  static int floatToIntBits(float float0) {
    return float0 = = 0.0F ? 0 : Float.floatToIntBits(float0);
  }

  static long doubleToLongBits(double double0) {
    return double0 = = 0.0 ? 0L : Double.doubleToLongBits(double0);
  }

private
  VecMathUtil() {}
}
} // namespace vecmath
} // namespace javax
