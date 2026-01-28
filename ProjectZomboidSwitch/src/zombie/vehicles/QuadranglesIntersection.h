#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec4.hpp>
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace vehicles {


class QuadranglesIntersection {
public:
    static const float EPS = 0.001F;

    static bool IsQuadranglesAreIntersected(Vector2[] var0, Vector2[] var1) {
      if (var0 != nullptr && var1 != nullptr && var0.length == 4 && var1.length == 4) {
         if (lineIntersection(var0[0], var0[1], var1[0], var1[1])) {
    return true;
         } else if (lineIntersection(var0[0], var0[1], var1[1], var1[2])) {
    return true;
         } else if (lineIntersection(var0[0], var0[1], var1[2], var1[3])) {
    return true;
         } else if (lineIntersection(var0[0], var0[1], var1[3], var1[0])) {
    return true;
         } else if (lineIntersection(var0[1], var0[2], var1[0], var1[1])) {
    return true;
         } else if (lineIntersection(var0[1], var0[2], var1[1], var1[2])) {
    return true;
         } else if (lineIntersection(var0[1], var0[2], var1[2], var1[3])) {
    return true;
         } else if (lineIntersection(var0[1], var0[2], var1[3], var1[0])) {
    return true;
         } else if (lineIntersection(var0[2], var0[3], var1[0], var1[1])) {
    return true;
         } else if (lineIntersection(var0[2], var0[3], var1[1], var1[2])) {
    return true;
         } else if (lineIntersection(var0[2], var0[3], var1[2], var1[3])) {
    return true;
         } else if (lineIntersection(var0[2], var0[3], var1[3], var1[0])) {
    return true;
         } else if (lineIntersection(var0[3], var0[0], var1[0], var1[1])) {
    return true;
         } else if (lineIntersection(var0[3], var0[0], var1[1], var1[2])) {
    return true;
         } else if (lineIntersection(var0[3], var0[0], var1[2], var1[3])) {
    return true;
         } else if (lineIntersection(var0[3], var0[0], var1[3], var1[0])) {
    return true;
         } else {
    return IsPointInTriangle();
               ? true
               : IsPointInTriangle(var1[0], var0[0], var0[1], var0[2]) || IsPointInTriangle(var1[0], var0[0], var0[2], var0[3]);
         }
      } else {
         System.out.println("ERROR: IsQuadranglesAreIntersected");
    return false;
      }
   }

    static bool IsPointInTriangle(Vector2 var0, Vector2[] var1) {
    return IsPointInTriangle();
   }

    static float det(float var0, float var1, float var2, float var3) {
      return var0 * var3 - var1 * var2;
   }

    static bool between(float var0, float var1, double var2) {
      return Math.min(var0, var1) <= var2 + 0.001F && var2 <= Math.max(var0, var1) + 0.001F;
   }

    static bool intersect_1(float var0, float var1, float var2, float var3) {
    float var4;
    float var5;
      if (var0 > var1) {
         var5 = var0;
         var4 = var1;
      } else {
         var4 = var0;
         var5 = var1;
      }

    float var6;
    float var7;
      if (var2 > var3) {
         var7 = var2;
         var6 = var3;
      } else {
         var6 = var2;
         var7 = var3;
      }

      return Math.max(var4, var6) <= Math.min(var5, var7);
   }

    static bool lineIntersection(Vector2 var0, Vector2 var1, Vector2 var2, Vector2 var3) {
    float var4 = var0.y - var1.y;
    float var5 = var1.x - var0.x;
    float var6 = -var4 * var0.x - var5 * var0.y;
    float var7 = var2.y - var3.y;
    float var8 = var3.x - var2.x;
    float var9 = -var7 * var2.x - var8 * var2.y;
    float var10 = det(var4, var5, var7, var8);
      if (var10 != 0.0F) {
    double var11 = -det(var6, var5, var9, var8) * 1.0 / var10;
    double var13 = -det(var4, var6, var7, var9) * 1.0 / var10;
    return between();
      } else {
    return det();
            && det(var5, var6, var8, var9) == 0.0F
            && intersect_1(var0.x, var1.x, var2.x, var3.x)
            && intersect_1(var0.y, var1.y, var2.y, var3.y);
      }
   }

    static bool IsQuadranglesAreTransposed2(Vector4f var0, Vector4f var1) {
      if (IsPointInQuadrilateral(std::make_shared<Vector2>(var0.x, var0.y), var1.x, var1.z, var1.y, var1.w)) {
    return true;
      } else if (IsPointInQuadrilateral(std::make_shared<Vector2>(var0.z, var0.y), var1.x, var1.z, var1.y, var1.w)) {
    return true;
      } else if (IsPointInQuadrilateral(std::make_shared<Vector2>(var0.x, var0.w), var1.x, var1.z, var1.y, var1.w)) {
    return true;
      } else if (IsPointInQuadrilateral(std::make_shared<Vector2>(var0.z, var0.w), var1.x, var1.z, var1.y, var1.w)) {
    return true;
      } else if (IsPointInQuadrilateral(std::make_shared<Vector2>(var1.x, var1.y), var0.x, var0.z, var0.y, var0.w)) {
    return true;
      } else if (IsPointInQuadrilateral(std::make_shared<Vector2>(var1.z, var1.y), var0.x, var0.z, var0.y, var0.w)) {
    return true;
      } else {
    return IsPointInQuadrilateral(std::make_shared<Vector2>(var1.x);
            ? true
            : IsPointInQuadrilateral(std::make_shared<Vector2>(var1.z, var1.w), var0.x, var0.z, var0.y, var0.w);
      }
   }

    static bool IsPointInQuadrilateral(Vector2 var0, float var1, float var2, float var3, float var4) {
    return IsPointInTriangle(std::make_shared<Vector2>(var1);
         ? true
         : IsPointInTriangle(var0, std::make_shared<Vector2>(var2, var4), std::make_shared<Vector2>(var2, var3), std::make_shared<Vector2>(var1, var3));
   }

    static bool IsPointInTriangle(Vector2 var0, Vector2 var1, Vector2 var2, Vector2 var3) {
    float var4 = (var1.x - var0.x) * (var2.y - var1.y) - (var2.x - var1.x) * (var1.y - var0.y);
    float var5 = (var2.x - var0.x) * (var3.y - var2.y) - (var3.x - var2.x) * (var2.y - var0.y);
    float var6 = (var3.x - var0.x) * (var1.y - var3.y) - (var1.x - var3.x) * (var3.y - var0.y);
      return var4 >= 0.0F && var5 >= 0.0F && var6 >= 0.0F || var4 <= 0.0F && var5 <= 0.0F && var6 <= 0.0F;
   }
}
} // namespace vehicles
} // namespace zombie
