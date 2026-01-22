#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Vector.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
    double vx;
    double vy;

   public CircleLineIntersect$RectVector(double var1, double var3) {
      this.vx = var1;
      this.vy = var3;
   }

   public CircleLineIntersect$RectVector(Vector var1) {
      this.setVector(var1);
   }

    double getLength() {
      return Math.sqrt(Math.abs(this.getvx() * this.getvx() + this.getvy() * this.getvy()));
   }

    Vector getUnitVector() {
    double var1 = this.getLength();
      return new CircleLineIntersect$RectVector(this.getvx() / var1, this.getvy() / var1);
   }

    double getvx() {
      return this.vx;
   }

    double getvy() {
      return this.vy;
   }

    void setVector(Vector var1) {
      this.vx = var1.getvx();
      this.vy = var1.getvy();
   }
}
} // namespace vehicles
} // namespace zombie
