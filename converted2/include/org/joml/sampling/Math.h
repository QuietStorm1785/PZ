#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
namespace sampling {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Math : public org {
public:
  static const double PI = java.lang.Math.PI;
  static const double PI2 = java.lang.Math.PI * 2;
  static const double PIHalf = java.lang.Math.PI / 2;
  static const double ONE_OVER_PI = 0.3183098861837907;
  static const double s5 = Double.longBitsToDouble(4523227044276562163L);
  static const double s4 = Double.longBitsToDouble(-4671934770969572232L);
  static const double s3 = Double.longBitsToDouble(4575957211482072852L);
  static const double s2 = Double.longBitsToDouble(-4628199223918090387L);
  static const double s1 = Double.longBitsToDouble(4607182418589157889L);

  static double sin_roquen_9(double double1) {
    double double0 = java.lang.Math.rint(double1 * 0.3183098861837907);
    double double2 = double1 - double0 * java.lang.Math.PI;
    double double3 = 1 - 2 * ((int)double0 & 1);
    double double4 = double2 * double2;
    double2 = double3 * double2;
    double double5 = s5;
    double5 = double5 * double4 + s4;
    double5 = double5 * double4 + s3;
    double5 = double5 * double4 + s2;
    double5 = double5 * double4 + s1;
    return double2 * double5;
  }
}
} // namespace sampling
} // namespace joml
} // namespace org
