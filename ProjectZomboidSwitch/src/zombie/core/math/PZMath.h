#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/Matrix4.h"
#include "zombie/core/math/Vector3.h"
// TODO: Add Quaternion implementation or use GLM if needed
#include "zombie/core/math/PZMath/SideOfLine.h"
#include "zombie/core/math/PZMath/UnitTests.h"
#include "zombie/iso/Vector2.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace math {


class PZMath {
public:
    static const float PI = (float) Math.PI;
    static const float PI2 = (float) (Math.PI * 2);
    static const float degToRads = (float) (Math.PI / 180.0);
    static const float radToDegs = 180.0F / (float)Math.PI;
    static const long microsToNanos = 1000L;
    static const long millisToMicros = 1000L;
    static const long secondsToMillis = 1000L;
    static long secondsToNanos = 1000000000L;

    static float almostUnitIdentity(float var0) {
      return var0 * var0 * (2.0F - var0);
   }

    static float almostIdentity(float var0, float var1, float var2) {
      if (var0 > var1) {
    return var0;
      } else {
    float var3 = 2.0F * var2 - var1;
    float var4 = 2.0F * var1 - 3.0F * var2;
    float var5 = var0 / var1;
         return (var3 * var5 + var4) * var5 * var5 + var2;
      }
   }

    static float gain(float var0, float var1) {
    float var2 = (float)(0.5 * Math.pow(2.0F * (var0 < 0.5F ? var0 : 1.0F - var0), var1));
      return var0 < 0.5F ? var2 : 1.0F - var2;
   }

    static float clamp(float var0, float var1, float var2) {
    float var3 = var0;
      if (var0 < var1) {
         var3 = var1;
      }

      if (var3 > var2) {
         var3 = var2;
      }

    return var3;
   }

    static long clamp(long var0, long var2, long var4) {
    long var6 = var0;
      if (var0 < var2) {
         var6 = var2;
      }

      if (var6 > var4) {
         var6 = var4;
      }

    return var6;
   }

    static int clamp(int var0, int var1, int var2) {
    int var3 = var0;
      if (var0 < var1) {
         var3 = var1;
      }

      if (var3 > var2) {
         var3 = var2;
      }

    return var3;
   }

    static float clampFloat(float var0, float var1, float var2) {
    return clamp();
   }

    static float clamp_01(float var0) {
    return clamp();
   }

    static float lerp(float var0, float var1, float var2) {
      return var0 + (var1 - var0) * var2;
   }

    static float lerpAngle(float var0, float var1, float var2) {
    float var3 = getClosestAngle(var0, var1);
    float var4 = var0 + var2 * var3;
    return wrap();
   }

    static Vector3f lerp(Vector3f var0, Vector3f var1, Vector3f var2, float var3) {
      var0.set(var1.x + (var2.x - var1.x) * var3, var1.y + (var2.y - var1.y) * var3, var1.z + (var2.z - var1.z) * var3);
    return var0;
   }

    static Vector2 lerp(Vector2 var0, Vector2 var1, Vector2 var2, float var3) {
      var0.set(var1.x + (var2.x - var1.x) * var3, var1.y + (var2.y - var1.y) * var3);
    return var0;
   }

    static float c_lerp(float var0, float var1, float var2) {
    float var3 = (float)(1.0 - Math.cos(var2 * (float) Math.PI)) / 2.0F;
      return var0 * (1.0F - var3) + var1 * var3;
   }

    static Quaternion slerp(Quaternion var0, Quaternion var1, Quaternion var2, float var3) {
    double var4 = var1.x * var2.x + var1.y * var2.y + var1.z * var2.z + var1.w * var2.w;
    double var6 = var4 < 0.0 ? -var4 : var4;
    double var8 = 1.0F - var3;
    double var10 = var3;
      if (1.0 - var6 > 0.1) {
    double var12 = org.joml.Math.acos(var6);
    double var14 = org.joml.Math.sin(var12);
    double var16 = 1.0 / var14;
         var8 = org.joml.Math.sin(var12 * (1.0 - var3)) * var16;
         var10 = org.joml.Math.sin(var12 * var3) * var16;
      }

      if (var4 < 0.0) {
         var10 = -var10;
      }

      var0.set(
         (float)(var8 * var1.x + var10 * var2.x),
         (float)(var8 * var1.y + var10 * var2.y),
         (float)(var8 * var1.z + var10 * var2.z),
         (float)(var8 * var1.w + var10 * var2.w)
      );
    return var0;
   }

    static float sqrt(float var0) {
      return org.joml.Math.sqrt(var0);
   }

    static float lerpFunc_EaseOutQuad(float var0) {
      return var0 * var0;
   }

    static float lerpFunc_EaseInQuad(float var0) {
    float var1 = 1.0F - var0;
      return 1.0F - var1 * var1;
   }

    static float lerpFunc_EaseOutInQuad(float var0) {
      return var0 < 0.5F ? lerpFunc_EaseOutQuad(var0) * 2.0F : 0.5F + lerpFunc_EaseInQuad(2.0F * var0 - 1.0F) / 2.0F;
   }

    static double tryParseDouble(const std::string& var0, double var1) {
      if (StringUtils.isNullOrWhitespace(var0)) {
    return var1;
      } else {
         try {
            return double.parseDouble(var0.trim());
         } catch (NumberFormatException var4) {
    return var1;
         }
      }
   }

    static float tryParseFloat(const std::string& var0, float var1) {
      if (StringUtils.isNullOrWhitespace(var0)) {
    return var1;
      } else {
         try {
            return float.parseFloat(var0.trim());
         } catch (NumberFormatException var3) {
    return var1;
         }
      }
   }

    static bool canParseFloat(const std::string& var0) {
      if (StringUtils.isNullOrWhitespace(var0)) {
    return false;
      } else {
         try {
            float.parseFloat(var0.trim());
    return true;
         } catch (NumberFormatException var2) {
    return false;
         }
      }
   }

    static int tryParseInt(const std::string& var0, int var1) {
      if (StringUtils.isNullOrWhitespace(var0)) {
    return var1;
      } else {
         try {
            return int.parseInt(var0.trim());
         } catch (NumberFormatException var3) {
    return var1;
         }
      }
   }

    static float degToRad(float var0) {
      return (float) (Math.PI / 180.0) * var0;
   }

    static float radToDeg(float var0) {
      return (180.0F / (float)Math.PI) * var0;
   }

    static float getClosestAngle(float var0, float var1) {
    float var2 = wrap(var0, (float) (Math.PI * 2));
    float var3 = wrap(var1, (float) (Math.PI * 2));
    float var4 = var3 - var2;
    return wrap();
   }

    static float getClosestAngleDegrees(float var0, float var1) {
    float var2 = degToRad(var0);
    float var3 = degToRad(var1);
    float var4 = getClosestAngle(var2, var3);
    return radToDeg();
   }

    static int sign(float var0) {
      return var0 > 0.0F ? 1 : (var0 < 0.0F ? -1 : 0);
   }

    static int fastfloor(double var0) {
    int var2 = (int)var0;
      return var0 < var2 ? var2 - 1 : var2;
   }

    static int fastfloor(float var0) {
    int var1 = (int)var0;
      return var0 < var1 ? var1 - 1 : var1;
   }

    static float floor(float var0) {
    return fastfloor();
   }

    static float ceil(float var0) {
      return var0 >= 0.0F ? (int)(var0 + 0.9999999F) : (int)(var0 - 1.0E-7F);
   }

    static float frac(float var0) {
    float var1 = floor(var0);
      return var0 - var1;
   }

    static float wrap(float var0, float var1) {
      if (var1 == 0.0F) {
         return 0.0F;
      } else if (var1 < 0.0F) {
         return 0.0F;
      } else if (var0 < 0.0F) {
    float var5 = -var0 / var1;
    float var6 = 1.0F - frac(var5);
         return var6 * var1;
      } else {
    float var2 = var0 / var1;
    float var3 = frac(var2);
         return var3 * var1;
      }
   }

    static float wrap(float var0, float var1, float var2) {
    float var3 = max(var2, var1);
    float var4 = min(var2, var1);
    float var5 = var3 - var4;
    float var6 = var0 - var4;
    float var7 = wrap(var6, var5);
      return var4 + var7;
   }

    static float max(float var0, float var1) {
      return var0 > var1 ? var0 : var1;
   }

    static int max(int var0, int var1) {
      return var0 > var1 ? var0 : var1;
   }

    static float min(float var0, float var1) {
      return var0 > var1 ? var1 : var0;
   }

    static int min(int var0, int var1) {
      return var0 > var1 ? var1 : var0;
   }

    static float abs(float var0) {
      return var0 * sign(var0);
   }

    static bool equal(float var0, float var1) {
    return equal();
   }

    static bool equal(float var0, float var1, float var2) {
    float var3 = var1 - var0;
    float var4 = abs(var3);
      return var4 < var2;
   }

    static Matrix4f convertMatrix(org.joml.Matrix4f var0, Matrix4f var1) {
      if (var1 == nullptr) {
         var1 = std::make_unique<Matrix4f>();
      }

      var1.m00 = var0.m00();
      var1.m01 = var0.m01();
      var1.m02 = var0.m02();
      var1.m03 = var0.m03();
      var1.m10 = var0.m10();
      var1.m11 = var0.m11();
      var1.m12 = var0.m12();
      var1.m13 = var0.m13();
      var1.m20 = var0.m20();
      var1.m21 = var0.m21();
      var1.m22 = var0.m22();
      var1.m23 = var0.m23();
      var1.m30 = var0.m30();
      var1.m31 = var0.m31();
      var1.m32 = var0.m32();
      var1.m33 = var0.m33();
    return var1;
   }

   public static org.joml.Matrix4f convertMatrix(Matrix4f var0, org.joml.Matrix4f var1) {
      if (var1 == nullptr) {
         var1 = new org.joml.Matrix4f();
      }

      return var1.set(
         var0.m00,
         var0.m01,
         var0.m02,
         var0.m03,
         var0.m10,
         var0.m11,
         var0.m12,
         var0.m13,
         var0.m20,
         var0.m21,
         var0.m22,
         var0.m23,
         var0.m30,
         var0.m31,
         var0.m32,
         var0.m33
      );
   }

    static float step(float var0, float var1, float var2) {
      if (var0 > var1) {
    return max(var0 +);
      } else {
         return var0 < var1 ? min(var0 + var2, var1) : var0;
      }
   }

    static SideOfLine testSideOfLine(float var0, float var1, float var2, float var3, float var4, float var5) {
    float var6 = (var4 - var0) * (var3 - var1) - (var5 - var1) * (var2 - var0);
      return var6 > 0.0F ? SideOfLine.Left : (var6 < 0.0F ? SideOfLine.Right : SideOfLine.OnLine);
   }

    static float roundToNearest(float var0) {
    int var1 = sign(var0);
    return floor(var0 +);
   }

    static int roundToInt(float var0) {
      return (int)(roundToNearest(var0) + 1.0E-4F);
   }

    static float roundToIntPlus05(float var0) {
    return floor();
   }

    static float roundFromEdges(float var0) {
    float var1 = (int)var0;
    float var2 = var0 - var1;
      if (var2 < 0.2F) {
         return var1 + 0.2F;
      } else {
         return var2 > 0.8F ? var1 + 1.0F - 0.2F : var0;
      }
   }

   static {
      UnitTests.runAll();
   }
}
} // namespace math
} // namespace core
} // namespace zombie
