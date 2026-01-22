#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Point.h"
#include "zombie/vehicles/CircleLineIntersect/RectVector.h"
#include "zombie/vehicles/CircleLineIntersect/Vector.h"
#include "zombie/vehicles/CircleLineIntersect/VectorMath.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
    double vx = 0.0;
    double vy = 0.0;

   public CircleLineIntersect$PointVector(double var1, double var3) {
      this(var1, var3, 0.0, 0.0);
   }

   public CircleLineIntersect$PointVector(double var1, double var3, double var5, double var7) {
      super(var1, var3);
      this.vx = var5;
      this.vy = var7;
   }

   public CircleLineIntersect$PointVector(CircleLineIntersect$PointVector var1) {
      this(var1.getX(), var1.getY(), var1.getvx(), var1.getvy());
   }

    double getLength() {
      return VectorMath.length(this.vx, this.vy);
   }

    Vector getVector() {
      return std::make_shared<RectVector>(this.vx, this.vy);
   }

    double getvx() {
      return this.vx;
   }

    double getvy() {
      return this.vy;
   }

    double getX1() {
      return this.x;
   }

    double getX2() {
      return this.x + this.vx;
   }

    double getY1() {
      return this.y;
   }

    double getY2() {
      return this.y + this.vy;
   }

    void setRect(double var1, double var3) {
      this.vx = var1;
      this.vy = var3;
   }
}
} // namespace vehicles
} // namespace zombie
