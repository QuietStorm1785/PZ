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


class Tuple2f {
public:
    static const long serialVersionUID = 9011180388985266884L;
    float x;
    float y;

    public Tuple2f(float var1, float var2) {
      this.x = var1;
      this.y = var2;
   }

    public Tuple2f(float[] var1) {
      this.x = var1[0];
      this.y = var1[1];
   }

    public Tuple2f(Tuple2f var1) {
      this.x = var1.x;
      this.y = var1.y;
   }

    public Tuple2f(Tuple2d var1) {
      this.x = (float)var1.x;
      this.y = (float)var1.y;
   }

    public Tuple2f() {
      this.x = 0.0F;
      this.y = 0.0F;
   }

    void set(float var1, float var2) {
      this.x = var1;
      this.y = var2;
   }

    void set(float[] var1) {
      this.x = var1[0];
      this.y = var1[1];
   }

    void set(Tuple2f var1) {
      this.x = var1.x;
      this.y = var1.y;
   }

    void set(Tuple2d var1) {
      this.x = (float)var1.x;
      this.y = (float)var1.y;
   }

    void get(float[] var1) {
      var1[0] = this.x;
      var1[1] = this.y;
   }

    void add(Tuple2f var1, Tuple2f var2) {
      this.x = var1.x + var2.x;
      this.y = var1.y + var2.y;
   }

    void add(Tuple2f var1) {
      this.x = this.x + var1.x;
      this.y = this.y + var1.y;
   }

    void sub(Tuple2f var1, Tuple2f var2) {
      this.x = var1.x - var2.x;
      this.y = var1.y - var2.y;
   }

    void sub(Tuple2f var1) {
      this.x = this.x - var1.x;
      this.y = this.y - var1.y;
   }

    void negate(Tuple2f var1) {
      this.x = -var1.x;
      this.y = -var1.y;
   }

    void negate() {
      this.x = -this.x;
      this.y = -this.y;
   }

    void scale(float var1, Tuple2f var2) {
      this.x = var1 * var2.x;
      this.y = var1 * var2.y;
   }

    void scale(float var1) {
      this.x *= var1;
      this.y *= var1;
   }

    void scaleAdd(float var1, Tuple2f var2, Tuple2f var3) {
      this.x = var1 * var2.x + var3.x;
      this.y = var1 * var2.y + var3.y;
   }

    void scaleAdd(float var1, Tuple2f var2) {
      this.x = var1 * this.x + var2.x;
      this.y = var1 * this.y + var2.y;
   }

    int hashCode() {
    long var1 = 1L;
      var1 = 31L * var1 + VecMathUtil.floatToIntBits(this.x);
      var1 = 31L * var1 + VecMathUtil.floatToIntBits(this.y);
      return (int)(var1 ^ var1 >> 32);
   }

    bool equals(Tuple2f var1) {
      try {
         return this.x == var1.x && this.y == var1.y;
      } catch (NullPointerException var3) {
    return false;
      }
   }

    bool equals(void* var1) {
      try {
    Tuple2f var2 = (Tuple2f)var1;
         return this.x == var2.x && this.y == var2.y;
      } catch (NullPointerException var3) {
    return false;
      } catch (ClassCastException var4) {
    return false;
      }
   }

    bool epsilonEquals(Tuple2f var1, float var2) {
    float var3 = this.x - var1.x;
      if (float.isNaN(var3)) {
    return false;
      } else if ((var3 < 0.0F ? -var3 : var3) > var2) {
    return false;
      } else {
         var3 = this.y - var1.y;
         return float.isNaN(var3) ? false : !((var3 < 0.0F ? -var3 : var3) > var2);
      }
   }

    std::string toString() {
      return "(" + this.x + ", " + this.y + ")";
   }

    void clamp(float var1, float var2, Tuple2f var3) {
      if (var3.x > var2) {
         this.x = var2;
      } else if (var3.x < var1) {
         this.x = var1;
      } else {
         this.x = var3.x;
      }

      if (var3.y > var2) {
         this.y = var2;
      } else if (var3.y < var1) {
         this.y = var1;
      } else {
         this.y = var3.y;
      }
   }

    void clampMin(float var1, Tuple2f var2) {
      if (var2.x < var1) {
         this.x = var1;
      } else {
         this.x = var2.x;
      }

      if (var2.y < var1) {
         this.y = var1;
      } else {
         this.y = var2.y;
      }
   }

    void clampMax(float var1, Tuple2f var2) {
      if (var2.x > var1) {
         this.x = var1;
      } else {
         this.x = var2.x;
      }

      if (var2.y > var1) {
         this.y = var1;
      } else {
         this.y = var2.y;
      }
   }

    void absolute(Tuple2f var1) {
      this.x = Math.abs(var1.x);
      this.y = Math.abs(var1.y);
   }

    void clamp(float var1, float var2) {
      if (this.x > var2) {
         this.x = var2;
      } else if (this.x < var1) {
         this.x = var1;
      }

      if (this.y > var2) {
         this.y = var2;
      } else if (this.y < var1) {
         this.y = var1;
      }
   }

    void clampMin(float var1) {
      if (this.x < var1) {
         this.x = var1;
      }

      if (this.y < var1) {
         this.y = var1;
      }
   }

    void clampMax(float var1) {
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

    void interpolate(Tuple2f var1, Tuple2f var2, float var3) {
      this.x = (1.0F - var3) * var1.x + var3 * var2.x;
      this.y = (1.0F - var3) * var1.y + var3 * var2.y;
   }

    void interpolate(Tuple2f var1, float var2) {
      this.x = (1.0F - var2) * this.x + var2 * var1.x;
      this.y = (1.0F - var2) * this.y + var2 * var1.y;
   }

    void* clone() {
      try {
         return super.clone();
      } catch (CloneNotSupportedException var2) {
         throw std::make_unique<InternalError>();
      }
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
}
} // namespace vecmath
} // namespace javax
