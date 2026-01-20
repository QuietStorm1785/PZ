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


class Vector4d : public Tuple4d {
public:
    static const long serialVersionUID = 3938123424117448700L;

    public Vector4d(double var1, double var3, double var5, double var7) {
      super(var1, var3, var5, var7);
   }

    public Vector4d(double[] var1) {
      super(var1);
   }

    public Vector4d(Vector4d var1) {
      super(var1);
   }

    public Vector4d(Vector4f var1) {
      super(var1);
   }

    public Vector4d(Tuple4f var1) {
      super(var1);
   }

    public Vector4d(Tuple4d var1) {
      super(var1);
   }

    public Vector4d(Tuple3d var1) {
      super(var1.x, var1.y, var1.z, 0.0);
   }

    public Vector4d() {
   }

    void set(Tuple3d var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.w = 0.0;
   }

    double length() {
      return Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z + this.w * this.w);
   }

    double lengthSquared() {
      return this.x * this.x + this.y * this.y + this.z * this.z + this.w * this.w;
   }

    double dot(Vector4d var1) {
      return this.x * var1.x + this.y * var1.y + this.z * var1.z + this.w * var1.w;
   }

    void normalize(Vector4d var1) {
    double var2 = 1.0 / Math.sqrt(var1.x * var1.x + var1.y * var1.y + var1.z * var1.z + var1.w * var1.w);
      this.x = var1.x * var2;
      this.y = var1.y * var2;
      this.z = var1.z * var2;
      this.w = var1.w * var2;
   }

    void normalize() {
    double var1 = 1.0 / Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z + this.w * this.w);
      this.x *= var1;
      this.y *= var1;
      this.z *= var1;
      this.w *= var1;
   }

    double angle(Vector4d var1) {
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
