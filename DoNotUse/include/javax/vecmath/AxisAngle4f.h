#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace vecmath {


class AxisAngle4f {
public:
    static const long serialVersionUID = -163246355858070601L;
    float x;
    float y;
    float z;
    float angle;
    static const double EPS = 1.0E-6;

    public AxisAngle4f(float var1, float var2, float var3, float var4) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.angle = var4;
   }

    public AxisAngle4f(float[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
      this.angle = var1[3];
   }

    public AxisAngle4f(AxisAngle4f var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.angle = var1.angle;
   }

    public AxisAngle4f(AxisAngle4d var1) {
      this.x = (float)var1.x;
      this.y = (float)var1.y;
      this.z = (float)var1.z;
      this.angle = (float)var1.angle;
   }

    public AxisAngle4f(Vector3f var1, float var2) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.angle = var2;
   }

    public AxisAngle4f() {
      this.x = 0.0F;
      this.y = 0.0F;
      this.z = 1.0F;
      this.angle = 0.0F;
   }

    void set(float var1, float var2, float var3, float var4) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.angle = var4;
   }

    void set(float[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
      this.angle = var1[3];
   }

    void set(AxisAngle4f var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.angle = var1.angle;
   }

    void set(AxisAngle4d var1) {
      this.x = (float)var1.x;
      this.y = (float)var1.y;
      this.z = (float)var1.z;
      this.angle = (float)var1.angle;
   }

    void set(Vector3f var1, float var2) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.angle = var2;
   }

    void get(float[] var1) {
      var1[0] = this.x;
      var1[1] = this.y;
      var1[2] = this.z;
      var1[3] = this.angle;
   }

    void set(Quat4f var1) {
    double var2 = var1.x * var1.x + var1.y * var1.y + var1.z * var1.z;
      if (var2 > 1.0E-6) {
         var2 = Math.sqrt(var2);
    double var4 = 1.0 / var2;
         this.x = (float)(var1.x * var4);
         this.y = (float)(var1.y * var4);
         this.z = (float)(var1.z * var4);
         this.angle = (float)(2.0 * Math.atan2(var2, var1.w));
      } else {
         this.x = 0.0F;
         this.y = 1.0F;
         this.z = 0.0F;
         this.angle = 0.0F;
      }
   }

    void set(Quat4d var1) {
    double var2 = var1.x * var1.x + var1.y * var1.y + var1.z * var1.z;
      if (var2 > 1.0E-6) {
         var2 = Math.sqrt(var2);
    double var4 = 1.0 / var2;
         this.x = (float)(var1.x * var4);
         this.y = (float)(var1.y * var4);
         this.z = (float)(var1.z * var4);
         this.angle = (float)(2.0 * Math.atan2(var2, var1.w));
      } else {
         this.x = 0.0F;
         this.y = 1.0F;
         this.z = 0.0F;
         this.angle = 0.0F;
      }
   }

    void set(Matrix4f var1) {
    Matrix3f var2 = std::make_shared<Matrix3f>();
      var1.get(var2);
      this.x = var2.m21 - var2.m12;
      this.y = var2.m02 - var2.m20;
      this.z = var2.m10 - var2.m01;
    double var3 = this.x * this.x + this.y * this.y + this.z * this.z;
      if (var3 > 1.0E-6) {
         var3 = Math.sqrt(var3);
    double var5 = 0.5 * var3;
    double var7 = 0.5 * (var2.m00 + var2.m11 + var2.m22 - 1.0);
         this.angle = (float)Math.atan2(var5, var7);
    double var9 = 1.0 / var3;
         this.x = (float)(this.x * var9);
         this.y = (float)(this.y * var9);
         this.z = (float)(this.z * var9);
      } else {
         this.x = 0.0F;
         this.y = 1.0F;
         this.z = 0.0F;
         this.angle = 0.0F;
      }
   }

    void set(Matrix4d var1) {
    Matrix3d var2 = std::make_shared<Matrix3d>();
      var1.get(var2);
      this.x = (float)(var2.m21 - var2.m12);
      this.y = (float)(var2.m02 - var2.m20);
      this.z = (float)(var2.m10 - var2.m01);
    double var3 = this.x * this.x + this.y * this.y + this.z * this.z;
      if (var3 > 1.0E-6) {
         var3 = Math.sqrt(var3);
    double var5 = 0.5 * var3;
    double var7 = 0.5 * (var2.m00 + var2.m11 + var2.m22 - 1.0);
         this.angle = (float)Math.atan2(var5, var7);
    double var9 = 1.0 / var3;
         this.x = (float)(this.x * var9);
         this.y = (float)(this.y * var9);
         this.z = (float)(this.z * var9);
      } else {
         this.x = 0.0F;
         this.y = 1.0F;
         this.z = 0.0F;
         this.angle = 0.0F;
      }
   }

    void set(Matrix3f var1) {
      this.x = var1.m21 - var1.m12;
      this.y = var1.m02 - var1.m20;
      this.z = var1.m10 - var1.m01;
    double var2 = this.x * this.x + this.y * this.y + this.z * this.z;
      if (var2 > 1.0E-6) {
         var2 = Math.sqrt(var2);
    double var4 = 0.5 * var2;
    double var6 = 0.5 * (var1.m00 + var1.m11 + var1.m22 - 1.0);
         this.angle = (float)Math.atan2(var4, var6);
    double var8 = 1.0 / var2;
         this.x = (float)(this.x * var8);
         this.y = (float)(this.y * var8);
         this.z = (float)(this.z * var8);
      } else {
         this.x = 0.0F;
         this.y = 1.0F;
         this.z = 0.0F;
         this.angle = 0.0F;
      }
   }

    void set(Matrix3d var1) {
      this.x = (float)(var1.m21 - var1.m12);
      this.y = (float)(var1.m02 - var1.m20);
      this.z = (float)(var1.m10 - var1.m01);
    double var2 = this.x * this.x + this.y * this.y + this.z * this.z;
      if (var2 > 1.0E-6) {
         var2 = Math.sqrt(var2);
    double var4 = 0.5 * var2;
    double var6 = 0.5 * (var1.m00 + var1.m11 + var1.m22 - 1.0);
         this.angle = (float)Math.atan2(var4, var6);
    double var8 = 1.0 / var2;
         this.x = (float)(this.x * var8);
         this.y = (float)(this.y * var8);
         this.z = (float)(this.z * var8);
      } else {
         this.x = 0.0F;
         this.y = 1.0F;
         this.z = 0.0F;
         this.angle = 0.0F;
      }
   }

    std::string toString() {
      return "(" + this.x + ", " + this.y + ", " + this.z + ", " + this.angle + ")";
   }

    bool equals(AxisAngle4f var1) {
      try {
         return this.x == var1.x && this.y == var1.y && this.z == var1.z && this.angle == var1.angle;
      } catch (NullPointerException var3) {
    return false;
      }
   }

    bool equals(void* var1) {
      try {
    AxisAngle4f var2 = (AxisAngle4f)var1;
         return this.x == var2.x && this.y == var2.y && this.z == var2.z && this.angle == var2.angle;
      } catch (NullPointerException var3) {
    return false;
      } catch (ClassCastException var4) {
    return false;
      }
   }

    bool epsilonEquals(AxisAngle4f var1, float var2) {
    float var3 = this.x - var1.x;
      if ((var3 < 0.0F ? -var3 : var3) > var2) {
    return false;
      } else {
         var3 = this.y - var1.y;
         if ((var3 < 0.0F ? -var3 : var3) > var2) {
    return false;
         } else {
            var3 = this.z - var1.z;
            if ((var3 < 0.0F ? -var3 : var3) > var2) {
    return false;
            } else {
               var3 = this.angle - var1.angle;
               return !((var3 < 0.0F ? -var3 : var3) > var2);
            }
         }
      }
   }

    int hashCode() {
    long var1 = 1L;
      var1 = 31L * var1 + VecMathUtil.floatToIntBits(this.x);
      var1 = 31L * var1 + VecMathUtil.floatToIntBits(this.y);
      var1 = 31L * var1 + VecMathUtil.floatToIntBits(this.z);
      var1 = 31L * var1 + VecMathUtil.floatToIntBits(this.angle);
      return (int)(var1 ^ var1 >> 32);
   }

    void* clone() {
      try {
         return super.clone();
      } catch (CloneNotSupportedException var2) {
         throw std::make_unique<InternalError>();
      }
   }

    float getAngle() {
      return this.angle;
   }

    void setAngle(float var1) {
      this.angle = var1;
   }

    float getX() {
      return this.x;
   }

    void setX(float var1) {
      this.x = var1;
   }

    float getY() {
      return this.y;
   }

    void setY(float var1) {
      this.y = var1;
   }

    float getZ() {
      return this.z;
   }

    void setZ(float var1) {
      this.z = var1;
   }
}
} // namespace vecmath
} // namespace javax
