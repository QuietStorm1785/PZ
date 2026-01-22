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


class Vector2d : public Tuple2d {
public:
    static const long serialVersionUID = 8572646365302599857L;

    public Vector2d(double var1, double var3) {
      super(var1, var3);
   }

    public Vector2d(double[] var1) {
      super(var1);
   }

    public Vector2d(Vector2d var1) {
      super(var1);
   }

    public Vector2d(Vector2f var1) {
      super(var1);
   }

    public Vector2d(Tuple2d var1) {
      super(var1);
   }

    public Vector2d(Tuple2f var1) {
      super(var1);
   }

    public Vector2d() {
   }

    double dot(Vector2d var1) {
      return this.x * var1.x + this.y * var1.y;
   }

    double length() {
      return Math.sqrt(this.x * this.x + this.y * this.y);
   }

    double lengthSquared() {
      return this.x * this.x + this.y * this.y;
   }

    void normalize(Vector2d var1) {
    double var2 = 1.0 / Math.sqrt(var1.x * var1.x + var1.y * var1.y);
      this.x = var1.x * var2;
      this.y = var1.y * var2;
   }

    void normalize() {
    double var1 = 1.0 / Math.sqrt(this.x * this.x + this.y * this.y);
      this.x *= var1;
      this.y *= var1;
   }

    double angle(Vector2d var1) {
    double var2 = this.dot(var1) / (this.length() * var1.length());
      if (var2 < -1.0) {
         var2 = -1.0;
      }

      if (var2 > 1.0) {
         var2 = 1.0;
      }

      return Math.acos(var2);
   }
}
} // namespace vecmath
} // namespace javax
