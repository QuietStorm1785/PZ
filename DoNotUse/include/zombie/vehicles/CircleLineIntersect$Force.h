#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/PointVector.h"
#include "zombie/vehicles/CircleLineIntersect/VectorMath.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
    double length;
    double mass;

   public CircleLineIntersect$Force(double var1, double var3, double var5, double var7) {
      super(var1, var3, var5, var7);
      this.length = VectorMath.length(var5, var7);
   }

    double getLength() {
      return this.length;
   }

    double getnormvx() {
      return this.length > 0.0 ? this.vx / this.length : 0.0;
   }

    double getnormvy() {
      return this.length > 0.0 ? this.vy / this.length : 0.0;
   }

    double getRestitution(void* var1) {
      return 1.0;
   }

    void setPointVector(PointVector var1) {
      this.x = var1.getX();
      this.y = var1.getY();
      if (!this.isFrozen() && (this.vx != var1.getvx() || this.vy != var1.getvy())) {
         this.vx = var1.getvx();
         this.vy = var1.getvy();
         this.length = VectorMath.length(this.vx, this.vy);
      }
   }

    bool isFrozen() {
    return false;
   }
}
} // namespace vehicles
} // namespace zombie
