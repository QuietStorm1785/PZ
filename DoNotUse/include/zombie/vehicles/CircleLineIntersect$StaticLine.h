#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Point.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
    double x2;
    double y2;

   public CircleLineIntersect$StaticLine(double var1, double var3, double var5, double var7) {
      super(var1, var3);
      this.x2 = var5;
      this.y2 = var7;
   }

    Point getP1() {
      return std::make_shared<Point>(this.getX1(), this.getY1());
   }

    Point getP2() {
      return std::make_shared<Point>(this.getX2(), this.getY2());
   }

    double getX1() {
      return this.x;
   }

    double getX2() {
      return this.x2;
   }

    double getY1() {
      return this.y;
   }

    double getY2() {
      return this.y2;
   }
}
} // namespace vehicles
} // namespace zombie
