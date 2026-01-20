#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class CircleLineIntersect {
public:
    double x;
    double y;

   public static const CircleLineIntersect$Point midpoint(double var0, double var2, double var4, double var6) {
      return new CircleLineIntersect$Point((var0 + var4) / 2.0, (var2 + var6) / 2.0);
   }

   public static const CircleLineIntersect$Point midpoint(CircleLineIntersect$Point var0, CircleLineIntersect$Point var1) {
    return midpoint();
   }

   public CircleLineIntersect$Point(double var1, double var3) {
      if (double.isNaN(var1) || double.isInfinite(var1)) {
         var1 = 0.0;
      }

      if (double.isNaN(var3) || double.isInfinite(var3)) {
         var3 = 0.0;
      }

      this.x = var1;
      this.y = var3;
   }

    double getX() {
      return this.x;
   }

    double getY() {
      return this.y;
   }

    void setPoint(double var1, double var3) {
      this.x = var1;
      this.y = var3;
   }

    static double distanceSq(double var0, double var2, double var4, double var6) {
      var0 -= var4;
      var2 -= var6;
      return var0 * var0 + var2 * var2;
   }

    static double distance(double var0, double var2, double var4, double var6) {
      var0 -= var4;
      var2 -= var6;
      return Math.sqrt(var0 * var0 + var2 * var2);
   }

    double distanceSq(double var1, double var3) {
      var1 -= this.getX();
      var3 -= this.getY();
      return var1 * var1 + var3 * var3;
   }

    double distanceSq(CircleLineIntersect$Point var1) {
    double var2 = var1.getX() - this.getX();
    double var4 = var1.getY() - this.getY();
      return var2 * var2 + var4 * var4;
   }

    double distance(CircleLineIntersect$Point var1) {
    double var2 = var1.getX() - this.getX();
    double var4 = var1.getY() - this.getY();
      return Math.sqrt(var2 * var2 + var4 * var4);
   }
}
} // namespace vehicles
} // namespace zombie
