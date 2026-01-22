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


class Vector2f : public Tuple2f {
public:
    static const long serialVersionUID = -2168194326883512320L;

    public Vector2f(float var1, float var2) {
      super(var1, var2);
   }

    public Vector2f(float[] var1) {
      super(var1);
   }

    public Vector2f(Vector2f var1) {
      super(var1);
   }

    public Vector2f(Vector2d var1) {
      super(var1);
   }

    public Vector2f(Tuple2f var1) {
      super(var1);
   }

    public Vector2f(Tuple2d var1) {
      super(var1);
   }

    public Vector2f() {
   }

    float dot(Vector2f var1) {
      return this.x * var1.x + this.y * var1.y;
   }

    float length() {
      return (float)Math.sqrt(this.x * this.x + this.y * this.y);
   }

    float lengthSquared() {
      return this.x * this.x + this.y * this.y;
   }

    void normalize(Vector2f var1) {
    float var2 = (float)(1.0 / Math.sqrt(var1.x * var1.x + var1.y * var1.y));
      this.x = var1.x * var2;
      this.y = var1.y * var2;
   }

    void normalize() {
    float var1 = (float)(1.0 / Math.sqrt(this.x * this.x + this.y * this.y));
      this.x *= var1;
      this.y *= var1;
   }

    float angle(Vector2f var1) {
    double var2 = this.dot(var1) / (this.length() * var1.length());
      if (var2 < -1.0) {
         var2 = -1.0;
      }

      if (var2 > 1.0) {
         var2 = 1.0;
      }

      return (float)Math.acos(var2);
   }
}
} // namespace vecmath
} // namespace javax
