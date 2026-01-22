#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Force.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
    double radius;
    double radiussq;

   public CircleLineIntersect$ForceCircle(double var1, double var3, double var5, double var7, double var9) {
      super(var1, var3, var5, var7);
      this.radius = var9;
      this.radiussq = var9 * var9;
   }

    double getRadius() {
      return this.radius;
   }

    double getRadiusSq() {
      return this.radiussq;
   }
}
} // namespace vehicles
} // namespace zombie
