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


class Tuple3d {
public:
    static const long serialVersionUID = 5542096614926168415L;
    double x;
    double y;
    double z;

    public Tuple3d(double var1, double var3, double var5) {
      this.x = var1;
      this.y = var3;
      this.z = var5;
   }

    public Tuple3d(double[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
   }

    public Tuple3d(Tuple3d var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
   }

    public Tuple3d(Tuple3f var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
   }

    public Tuple3d() {
      this.x = 0.0;
      this.y = 0.0;
      this.z = 0.0;
   }

    void set(double var1, double var3, double var5) {
      this.x = var1;
      this.y = var3;
      this.z = var5;
   }

    void set(double[] var1) {
      this.x = var1[0];
      this.y = var1[1];
      this.z = var1[2];
   }

    void set(Tuple3d var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
   }

    void set(Tuple3f var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
   }

    void get(double[] var1) {
      var1[0] = this.x;
      var1[1] = this.y;
      var1[2] = this.z;
   }

    void get(Tuple3d var1) {
      var1.x = this.x;
      var1.y = this.y;
      var1.z = this.z;
   }

    void add(Tuple3d var1, Tuple3d var2) {
      this.x = var1.x + var2.x;
      this.y = var1.y + var2.y;
      this.z = var1.z + var2.z;
   }

    void add(Tuple3d var1) {
      this.x = this.x + var1.x;
      this.y = this.y + var1.y;
      this.z = this.z + var1.z;
   }

    void sub(Tuple3d var1, Tuple3d var2) {
      this.x = var1.x - var2.x;
      this.y = var1.y - var2.y;
      this.z = var1.z - var2.z;
   }

    void sub(Tuple3d var1) {
      this.x = this.x - var1.x;
      this.y = this.y - var1.y;
      this.z = this.z - var1.z;
   }

    void negate(Tuple3d var1) {
      this.x = -var1.x;
      this.y = -var1.y;
      this.z = -var1.z;
   }

    void negate() {
      this.x = -this.x;
      this.y = -this.y;
      this.z = -this.z;
   }

    void scale(double var1, Tuple3d var3) {
      this.x = var1 * var3.x;
      this.y = var1 * var3.y;
      this.z = var1 * var3.z;
   }

    void scale(double var1) {
      this.x *= var1;
      this.y *= var1;
      this.z *= var1;
   }

    void scaleAdd(double var1, Tuple3d var3, Tuple3d var4) {
      this.x = var1 * var3.x + var4.x;
      this.y = var1 * var3.y + var4.y;
      this.z = var1 * var3.z + var4.z;
   }

   /** @deprecated */
    void scaleAdd(double var1, Tuple3f var3) {
      this.scaleAdd(var1, std::make_shared<Point3d>(var3));
   }

    void scaleAdd(double var1, Tuple3d var3) {
      this.x = var1 * this.x + var3.x;
      this.y = var1 * this.y + var3.y;
      this.z = var1 * this.z + var3.z;
   }

    std::string toString() {
      return "(" + this.x + ", " + this.y + ", " + this.z + ")";
   }

    int hashCode() {
    long var1 = 1L;
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.x);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.y);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.z);
      return (int)(var1 ^ var1 >> 32);
   }

    bool equals(Tuple3d var1) {
      try {
         return this.x == var1.x && this.y == var1.y && this.z == var1.z;
      } catch (NullPointerException var3) {
    return false;
      }
   }

    bool equals(void* var1) {
      try {
    Tuple3d var2 = (Tuple3d)var1;
         return this.x == var2.x && this.y == var2.y && this.z == var2.z;
      } catch (ClassCastException var3) {
    return false;
      } catch (NullPointerException var4) {
    return false;
      }
   }

    bool epsilonEquals(Tuple3d var1, double var2) {
    double var4 = this.x - var1.x;
      if (double.isNaN(var4)) {
    return false;
      } else if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
      } else {
         var4 = this.y - var1.y;
         if (double.isNaN(var4)) {
    return false;
         } else if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
         } else {
            var4 = this.z - var1.z;
            return double.isNaN(var4) ? false : !((var4 < 0.0 ? -var4 : var4) > var2);
         }
      }
   }

   /** @deprecated */
    void clamp(float var1, float var2, Tuple3d var3) {
      this.clamp((double)var1, (double)var2, var3);
   }

    void clamp(double var1, double var3, Tuple3d var5) {
      if (var5.x > var3) {
         this.x = var3;
      } else if (var5.x < var1) {
         this.x = var1;
      } else {
         this.x = var5.x;
      }

      if (var5.y > var3) {
         this.y = var3;
      } else if (var5.y < var1) {
         this.y = var1;
      } else {
         this.y = var5.y;
      }

      if (var5.z > var3) {
         this.z = var3;
      } else if (var5.z < var1) {
         this.z = var1;
      } else {
         this.z = var5.z;
      }
   }

   /** @deprecated */
    void clampMin(float var1, Tuple3d var2) {
      this.clampMin((double)var1, var2);
   }

    void clampMin(double var1, Tuple3d var3) {
      if (var3.x < var1) {
         this.x = var1;
      } else {
         this.x = var3.x;
      }

      if (var3.y < var1) {
         this.y = var1;
      } else {
         this.y = var3.y;
      }

      if (var3.z < var1) {
         this.z = var1;
      } else {
         this.z = var3.z;
      }
   }

   /** @deprecated */
    void clampMax(float var1, Tuple3d var2) {
      this.clampMax((double)var1, var2);
   }

    void clampMax(double var1, Tuple3d var3) {
      if (var3.x > var1) {
         this.x = var1;
      } else {
         this.x = var3.x;
      }

      if (var3.y > var1) {
         this.y = var1;
      } else {
         this.y = var3.y;
      }

      if (var3.z > var1) {
         this.z = var1;
      } else {
         this.z = var3.z;
      }
   }

    void absolute(Tuple3d var1) {
      this.x = Math.abs(var1.x);
      this.y = Math.abs(var1.y);
      this.z = Math.abs(var1.z);
   }

   /** @deprecated */
    void clamp(float var1, float var2) {
      this.clamp((double)var1, (double)var2);
   }

    void clamp(double var1, double var3) {
      if (this.x > var3) {
         this.x = var3;
      } else if (this.x < var1) {
         this.x = var1;
      }

      if (this.y > var3) {
         this.y = var3;
      } else if (this.y < var1) {
         this.y = var1;
      }

      if (this.z > var3) {
         this.z = var3;
      } else if (this.z < var1) {
         this.z = var1;
      }
   }

   /** @deprecated */
    void clampMin(float var1) {
      this.clampMin((double)var1);
   }

    void clampMin(double var1) {
      if (this.x < var1) {
         this.x = var1;
      }

      if (this.y < var1) {
         this.y = var1;
      }

      if (this.z < var1) {
         this.z = var1;
      }
   }

   /** @deprecated */
    void clampMax(float var1) {
      this.clampMax((double)var1);
   }

    void clampMax(double var1) {
      if (this.x > var1) {
         this.x = var1;
      }

      if (this.y > var1) {
         this.y = var1;
      }

      if (this.z > var1) {
         this.z = var1;
      }
   }

    void absolute() {
      this.x = Math.abs(this.x);
      this.y = Math.abs(this.y);
      this.z = Math.abs(this.z);
   }

   /** @deprecated */
    void interpolate(Tuple3d var1, Tuple3d var2, float var3) {
      this.interpolate(var1, var2, (double)var3);
   }

    void interpolate(Tuple3d var1, Tuple3d var2, double var3) {
      this.x = (1.0 - var3) * var1.x + var3 * var2.x;
      this.y = (1.0 - var3) * var1.y + var3 * var2.y;
      this.z = (1.0 - var3) * var1.z + var3 * var2.z;
   }

   /** @deprecated */
    void interpolate(Tuple3d var1, float var2) {
      this.interpolate(var1, (double)var2);
   }

    void interpolate(Tuple3d var1, double var2) {
      this.x = (1.0 - var2) * this.x + var2 * var1.x;
      this.y = (1.0 - var2) * this.y + var2 * var1.y;
      this.z = (1.0 - var2) * this.z + var2 * var1.z;
   }

    void* clone() {
      try {
         return super.clone();
      } catch (CloneNotSupportedException var2) {
         throw std::make_unique<InternalError>();
      }
   }

    double getX() {
      return this.x;
   }

    void setX(double var1) {
      this.x = var1;
   }

    double getY() {
      return this.y;
   }

    void setY(double var1) {
      this.y = var1;
   }

    double getZ() {
      return this.z;
   }

    void setZ(double var1) {
      this.z = var1;
   }
}
} // namespace vecmath
} // namespace javax
