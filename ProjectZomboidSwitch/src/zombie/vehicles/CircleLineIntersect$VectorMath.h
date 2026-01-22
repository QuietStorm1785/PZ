#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Point.h"
#include "zombie/vehicles/CircleLineIntersect/RectVector.h"
#include "zombie/vehicles/CircleLineIntersect/StaticLine.h"
#include "zombie/vehicles/CircleLineIntersect/Vector.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
    static Vector add(Vector var0, Vector var1) {
      return std::make_shared<RectVector>(var0.getvx() + var1.getvx(), var0.getvy() + var1.getvy());
   }

    static Vector subtract(Vector var0, Vector var1) {
      return std::make_shared<RectVector>(var0.getvx() - var1.getvx(), var0.getvy() - var1.getvy());
   }

    static double length(double var0, double var2) {
      return Point.distance(0.0, 0.0, var0, var2);
   }

    static double dotproduct(Vector var0, Vector var1) {
    return dotproduct();
   }

    static double dotproduct(double var0, double var2, double var4, double var6) {
      return var0 * var4 + var2 * var6;
   }

    static double cosproj(Vector var0, Vector var1) {
    return dotproduct();
   }

    static double cosproj(double var0, double var2, double var4, double var6) {
    return dotproduct();
   }

    static double anglebetween(Vector var0, Vector var1) {
      return Math.acos(cosproj(var0, var1));
   }

    static double anglebetween(double var0, double var2, double var4, double var6) {
      return Math.acos(cosproj(var0, var2, var4, var6));
   }

    static double crossproduct(Vector var0, Vector var1) {
    return crossproduct();
   }

    static double crossproduct(double var0, double var2, double var4, double var6) {
      return var0 * var6 - var2 * var4;
   }

    static double sinproj(Vector var0, Vector var1) {
    return crossproduct();
   }

    static double sinproj(double var0, double var2, double var4, double var6) {
    return crossproduct();
   }

    static bool equaldirection(double var0, double var2, double var4, double var6, double var8, double var10, double var12, double var14) {
      if (var0 - var4 == 0.0 && var2 - var6 == 0.0) {
    return true;
      } else {
    double var16 = ((var0 - var4) * (var0 - var8) + (var2 - var6) * (var2 - var10)) / (Math.abs(var12) * Math.abs(var14));
         return var16 > 0.995 && var16 <= 1.0;
      }
   }

   public static const boolean equaldirection(
      double var0, double var2, double var4, double var6, double var8, double var10, double var12, double var14, double var16
   ) {
      if (var0 - var4 == 0.0 && var2 - var6 == 0.0) {
    return true;
      } else {
    double var18 = ((var0 - var4) * (var0 - var8) + (var2 - var6) * (var2 - var10)) / (Math.abs(var12) * Math.abs(var14));
         return var18 > var16 && var18 <= 1.0;
      }
   }

    static bool equaldirection(double var0, double var2, double var4, double var6, double var8, double var10, double var12) {
      if (var0 == 0.0 && var2 == 0.0) {
    return true;
      } else {
    double var14 = (var0 * var4 + var2 * var6) / (Math.abs(var8) * Math.abs(var10));
         return var14 > var12 && var14 <= 1.0;
      }
   }

    static bool equaldirection(double var0, double var2, double var4) {
      if (var0 > Math.PI * 2) {
         var0 -= Math.PI * 2;
      } else if (var0 < 0.0) {
         var0 += Math.PI * 2;
      }

      if (var2 > Math.PI * 2) {
         var2 -= Math.PI * 2;
      } else if (var2 < 0.0) {
         var2 += Math.PI * 2;
      }

      return Math.abs(var0 - var2) < var4;
   }

    static double linepointdistance(double var0, double var2, double var4, double var6, double var8, double var10) {
    Point var12 = closestpointonline(var0, var2, var4, var6, var8, var10);
      return Point.distance(var8, var10, var12.getX(), var12.getY());
   }

    static double linepointdistancesq(double var0, double var2, double var4, double var6, double var8, double var10) {
    double var12 = var6 - var2;
    double var14 = var0 - var4;
    double var16 = (var6 - var2) * var0 + (var0 - var4) * var2;
    double var18 = -var14 * var8 + var12 * var10;
    double var20 = var12 * var12 - -var14 * var14;
    double var22 = 0.0;
    double var24 = 0.0;
      if (var20 != 0.0) {
         var22 = (var12 * var16 - var14 * var18) / var20;
         var24 = (var12 * var18 - -var14 * var16) / var20;
      }

      return Math.abs((var22 - var8) * (var22 - var8) + (var24 - var10) * (var24 - var10));
   }

    static Point closestpointonline(StaticLine var0, Point var1) {
    return closestpointonline();
   }

    static Point closestpointonline(double var0, double var2, double var4, double var6, double var8, double var10) {
    double var12 = var6 - var2;
    double var14 = var0 - var4;
    double var16 = (var6 - var2) * var0 + (var0 - var4) * var2;
    double var18 = -var14 * var8 + var12 * var10;
    double var20 = var12 * var12 - -var14 * var14;
    double var22 = 0.0;
    double var24 = 0.0;
      if (var20 != 0.0) {
         var22 = (var12 * var16 - var14 * var18) / var20;
         var24 = (var12 * var18 - -var14 * var16) / var20;
      } else {
         var22 = var8;
         var24 = var10;
      }

      return std::make_shared<Point>(var22, var24);
   }

    static Vector getVector(Point var0, Point var1) {
      return std::make_shared<RectVector>(var0.getX() - var1.getX(), var0.getY() - var1.getY());
   }

    static Vector rotate(Vector var0, double var1) {
      return std::make_shared<RectVector>(var0.getvx() * Math.cos(var1) - var0.getvy() * Math.sin(var1), var0.getvx() * Math.sin(var1) + var0.getvy() * Math.cos(var1));
   }
}
} // namespace vehicles
} // namespace zombie
