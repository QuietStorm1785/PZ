package zombie.core.math;

import org.lwjgl.util.vector.Matrix4f;
import org.lwjgl.util.vector.Quaternion;
import org.lwjgl.util.vector.Vector3f;
import zombie.core.math.PZMath.SideOfLine;
import zombie.core.math.PZMath.UnitTests;
import zombie.iso.Vector2;
import zombie.util.StringUtils;

public final class PZMath {
   public static final float PI = (float) Math.PI;
   public static final float PI2 = (float) (Math.PI * 2);
   public static final float degToRads = (float) (Math.PI / 180.0);
   public static final float radToDegs = 180.0F / (float)Math.PI;
   public static final long microsToNanos = 1000L;
   public static final long millisToMicros = 1000L;
   public static final long secondsToMillis = 1000L;
   public static long secondsToNanos = 1000000000L;

   public static float almostUnitIdentity(float var0) {
      return var0 * var0 * (2.0F - var0);
   }

   public static float almostIdentity(float var0, float var1, float var2) {
      if (var0 > var1) {
         return var0;
      } else {
         float var3 = 2.0F * var2 - var1;
         float var4 = 2.0F * var1 - 3.0F * var2;
         float var5 = var0 / var1;
         return (var3 * var5 + var4) * var5 * var5 + var2;
      }
   }

   public static float gain(float var0, float var1) {
      float var2 = (float)(0.5 * Math.pow(2.0F * (var0 < 0.5F ? var0 : 1.0F - var0), var1));
      return var0 < 0.5F ? var2 : 1.0F - var2;
   }

   public static float clamp(float var0, float var1, float var2) {
      float var3 = var0;
      if (var0 < var1) {
         var3 = var1;
      }

      if (var3 > var2) {
         var3 = var2;
      }

      return var3;
   }

   public static long clamp(long var0, long var2, long var4) {
      long var6 = var0;
      if (var0 < var2) {
         var6 = var2;
      }

      if (var6 > var4) {
         var6 = var4;
      }

      return var6;
   }

   public static int clamp(int var0, int var1, int var2) {
      int var3 = var0;
      if (var0 < var1) {
         var3 = var1;
      }

      if (var3 > var2) {
         var3 = var2;
      }

      return var3;
   }

   public static float clampFloat(float var0, float var1, float var2) {
      return clamp(var0, var1, var2);
   }

   public static float clamp_01(float var0) {
      return clamp(var0, 0.0F, 1.0F);
   }

   public static float lerp(float var0, float var1, float var2) {
      return var0 + (var1 - var0) * var2;
   }

   public static float lerpAngle(float var0, float var1, float var2) {
      float var3 = getClosestAngle(var0, var1);
      float var4 = var0 + var2 * var3;
      return wrap(var4, (float) -Math.PI, (float) Math.PI);
   }

   public static Vector3f lerp(Vector3f var0, Vector3f var1, Vector3f var2, float var3) {
      var0.set(var1.x + (var2.x - var1.x) * var3, var1.y + (var2.y - var1.y) * var3, var1.z + (var2.z - var1.z) * var3);
      return var0;
   }

   public static Vector2 lerp(Vector2 var0, Vector2 var1, Vector2 var2, float var3) {
      var0.set(var1.x + (var2.x - var1.x) * var3, var1.y + (var2.y - var1.y) * var3);
      return var0;
   }

   public static float c_lerp(float var0, float var1, float var2) {
      float var3 = (float)(1.0 - Math.cos(var2 * (float) Math.PI)) / 2.0F;
      return var0 * (1.0F - var3) + var1 * var3;
   }

   public static Quaternion slerp(Quaternion var0, Quaternion var1, Quaternion var2, float var3) {
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

   public static float sqrt(float var0) {
      return org.joml.Math.sqrt(var0);
   }

   public static float lerpFunc_EaseOutQuad(float var0) {
      return var0 * var0;
   }

   public static float lerpFunc_EaseInQuad(float var0) {
      float var1 = 1.0F - var0;
      return 1.0F - var1 * var1;
   }

   public static float lerpFunc_EaseOutInQuad(float var0) {
      return var0 < 0.5F ? lerpFunc_EaseOutQuad(var0) * 2.0F : 0.5F + lerpFunc_EaseInQuad(2.0F * var0 - 1.0F) / 2.0F;
   }

   public static double tryParseDouble(String var0, double var1) {
      if (StringUtils.isNullOrWhitespace(var0)) {
         return var1;
      } else {
         try {
            return Double.parseDouble(var0.trim());
         } catch (NumberFormatException var4) {
            return var1;
         }
      }
   }

   public static float tryParseFloat(String var0, float var1) {
      if (StringUtils.isNullOrWhitespace(var0)) {
         return var1;
      } else {
         try {
            return Float.parseFloat(var0.trim());
         } catch (NumberFormatException var3) {
            return var1;
         }
      }
   }

   public static boolean canParseFloat(String var0) {
      if (StringUtils.isNullOrWhitespace(var0)) {
         return false;
      } else {
         try {
            Float.parseFloat(var0.trim());
            return true;
         } catch (NumberFormatException var2) {
            return false;
         }
      }
   }

   public static int tryParseInt(String var0, int var1) {
      if (StringUtils.isNullOrWhitespace(var0)) {
         return var1;
      } else {
         try {
            return Integer.parseInt(var0.trim());
         } catch (NumberFormatException var3) {
            return var1;
         }
      }
   }

   public static float degToRad(float var0) {
      return (float) (Math.PI / 180.0) * var0;
   }

   public static float radToDeg(float var0) {
      return (180.0F / (float)Math.PI) * var0;
   }

   public static float getClosestAngle(float var0, float var1) {
      float var2 = wrap(var0, (float) (Math.PI * 2));
      float var3 = wrap(var1, (float) (Math.PI * 2));
      float var4 = var3 - var2;
      return wrap(var4, (float) -Math.PI, (float) Math.PI);
   }

   public static float getClosestAngleDegrees(float var0, float var1) {
      float var2 = degToRad(var0);
      float var3 = degToRad(var1);
      float var4 = getClosestAngle(var2, var3);
      return radToDeg(var4);
   }

   public static int sign(float var0) {
      return var0 > 0.0F ? 1 : (var0 < 0.0F ? -1 : 0);
   }

   public static int fastfloor(double var0) {
      int var2 = (int)var0;
      return var0 < var2 ? var2 - 1 : var2;
   }

   public static int fastfloor(float var0) {
      int var1 = (int)var0;
      return var0 < var1 ? var1 - 1 : var1;
   }

   public static float floor(float var0) {
      return fastfloor(var0);
   }

   public static float ceil(float var0) {
      return var0 >= 0.0F ? (int)(var0 + 0.9999999F) : (int)(var0 - 1.0E-7F);
   }

   public static float frac(float var0) {
      float var1 = floor(var0);
      return var0 - var1;
   }

   public static float wrap(float var0, float var1) {
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

   public static float wrap(float var0, float var1, float var2) {
      float var3 = max(var2, var1);
      float var4 = min(var2, var1);
      float var5 = var3 - var4;
      float var6 = var0 - var4;
      float var7 = wrap(var6, var5);
      return var4 + var7;
   }

   public static float max(float var0, float var1) {
      return var0 > var1 ? var0 : var1;
   }

   public static int max(int var0, int var1) {
      return var0 > var1 ? var0 : var1;
   }

   public static float min(float var0, float var1) {
      return var0 > var1 ? var1 : var0;
   }

   public static int min(int var0, int var1) {
      return var0 > var1 ? var1 : var0;
   }

   public static float abs(float var0) {
      return var0 * sign(var0);
   }

   public static boolean equal(float var0, float var1) {
      return equal(var0, var1, 1.0E-7F);
   }

   public static boolean equal(float var0, float var1, float var2) {
      float var3 = var1 - var0;
      float var4 = abs(var3);
      return var4 < var2;
   }

   public static Matrix4f convertMatrix(org.joml.Matrix4f var0, Matrix4f var1) {
      if (var1 == null) {
         var1 = new Matrix4f();
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
      if (var1 == null) {
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

   public static float step(float var0, float var1, float var2) {
      if (var0 > var1) {
         return max(var0 + var2, var1);
      } else {
         return var0 < var1 ? min(var0 + var2, var1) : var0;
      }
   }

   public static SideOfLine testSideOfLine(float var0, float var1, float var2, float var3, float var4, float var5) {
      float var6 = (var4 - var0) * (var3 - var1) - (var5 - var1) * (var2 - var0);
      return var6 > 0.0F ? SideOfLine.Left : (var6 < 0.0F ? SideOfLine.Right : SideOfLine.OnLine);
   }

   public static float roundToNearest(float var0) {
      int var1 = sign(var0);
      return floor(var0 + 0.5F * var1);
   }

   public static int roundToInt(float var0) {
      return (int)(roundToNearest(var0) + 1.0E-4F);
   }

   public static float roundToIntPlus05(float var0) {
      return floor(var0) + 0.5F;
   }

   public static float roundFromEdges(float var0) {
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
