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


class Tuple2d {
public:
    static const long serialVersionUID = 6205762482756093838L;
    double x;
    double y;

    public Tuple2d(double var1, double var3) {
      this.x = var1;
      this.y = var3;
   }

    public Tuple2d(double[] var1) {
      this.x = var1[0];
      this.y = var1[1];
   }

    public Tuple2d(Tuple2d var1) {
      this.x = var1.x;
      this.y = var1.y;
   }

    public Tuple2d(Tuple2f var1) {
      this.x = var1.x;
      this.y = var1.y;
   }

    public Tuple2d() {
      this.x = 0.0;
      this.y = 0.0;
   }

    void set(double var1, double var3) {
      this.x = var1;
      this.y = var3;
   }

    void set(double[] var1) {
      this.x = var1[0];
      this.y = var1[1];
   }

    void set(Tuple2d var1) {
      this.x = var1.x;
      this.y = var1.y;
   }

    void set(Tuple2f var1) {
      this.x = var1.x;
      this.y = var1.y;
   }

    void get(double[] var1) {
      var1[0] = this.x;
      var1[1] = this.y;
   }

    void add(Tuple2d var1, Tuple2d var2) {
      this.x = var1.x + var2.x;
      this.y = var1.y + var2.y;
   }

    void add(Tuple2d var1) {
      this.x = this.x + var1.x;
      this.y = this.y + var1.y;
   }

    void sub(Tuple2d var1, Tuple2d var2) {
      this.x = var1.x - var2.x;
      this.y = var1.y - var2.y;
   }

    void sub(Tuple2d var1) {
      this.x = this.x - var1.x;
      this.y = this.y - var1.y;
   }

    void negate(Tuple2d var1) {
      this.x = -var1.x;
      this.y = -var1.y;
   }

    void negate() {
      this.x = -this.x;
      this.y = -this.y;
   }

    void scale(double var1, Tuple2d var3) {
      this.x = var1 * var3.x;
      this.y = var1 * var3.y;
   }

    void scale(double var1) {
      this.x *= var1;
      this.y *= var1;
   }

    void scaleAdd(double var1, Tuple2d var3, Tuple2d var4) {
      this.x = var1 * var3.x + var4.x;
      this.y = var1 * var3.y + var4.y;
   }

    void scaleAdd(double var1, Tuple2d var3) {
      this.x = var1 * this.x + var3.x;
      this.y = var1 * this.y + var3.y;
   }

    int hashCode() {
    long var1 = 1L;
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.x);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.y);
      return (int)(var1 ^ var1 >> 32);
   }

    bool equals(Tuple2d var1) {
      try {
         return this.x == var1.x && this.y == var1.y;
      } catch (NullPointerException var3) {
    return false;
      }
   }

    bool equals(void* var1) {
      try {
    Tuple2d var2 = (Tuple2d)var1;
         return this.x == var2.x && this.y == var2.y;
      } catch (NullPointerException var3) {
    return false;
      } catch (ClassCastException var4) {
    return false;
      }
   }

    bool epsilonEquals(Tuple2d var1, double var2) {
    double var4 = this.x - var1.x;
      if (double.isNaN(var4)) {
    return false;
      } else if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
      } else {
         var4 = this.y - var1.y;
         return double.isNaN(var4) ? false : !((var4 < 0.0 ? -var4 : var4) > var2);
      }
   }

    std::string toString() {
      return "(" + this.x + ", " + this.y + ")";
   }

    void clamp(double var1, double var3, Tuple2d var5) {
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
   }

    void clampMin(double var1, Tuple2d var3) {
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
   }

    void clampMax(double var1, Tuple2d var3) {
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
   }

    void absolute(Tuple2d var1) {
      this.x = Math.abs(var1.x);
      this.y = Math.abs(var1.y);
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
   }

    void clampMin(double var1) {
      if (this.x < var1) {
         this.x = var1;
      }

      if (this.y < var1) {
         this.y = var1;
      }
   }

    void clampMax(double var1) {
      if (this.x > var1) {
         this.x = var1;
      }

      if (this.y > var1) {
         this.y = var1;
      }
   }

    void absolute() {
      this.x = Math.abs(this.x);
      this.y = Math.abs(this.y);
   }

    void interpolate(Tuple2d var1, Tuple2d var2, double var3) {
      this.x = (1.0 - var3) * var1.x + var3 * var2.x;
      this.y = (1.0 - var3) * var1.y + var3 * var2.y;
   }

    void interpolate(Tuple2d var1, double var2) {
      this.x = (1.0 - var2) * this.x + var2 * var1.x;
      this.y = (1.0 - var2) * this.y + var2 * var1.y;
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
}
} // namespace vecmath
} // namespace javax
