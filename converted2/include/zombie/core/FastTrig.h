#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FastTrig {
public:
  static double cos(double double0) { return sin(double0 +); }

  static double sin(double double0) {
    double0 = reduceSinAngle(double0);
    return Math.abs(double0) <= Math.PI / 4 ? Math.sin(double0)
                                            : Math.cos((Math.PI / 2) - double0);
  }

  static double reduceSinAngle(double double0) {
    double0 %= Math.PI * 2;
    if (Math.abs(double0) > Math.PI) {
      double0 -= Math.PI * 2;
    }

    if (Math.abs(double0) > Math.PI / 2) {
      double0 = Math.PI - double0;
    }

    return double0;
  }
}
} // namespace core
} // namespace zombie
