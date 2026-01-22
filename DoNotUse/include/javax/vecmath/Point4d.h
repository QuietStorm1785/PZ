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


class Point4d : public Tuple4d {
public:
    static const long serialVersionUID = 1733471895962736949L;

    public Point4d(double var1, double var3, double var5, double var7) {
      super(var1, var3, var5, var7);
   }

    public Point4d(double[] var1) {
      super(var1);
   }

    public Point4d(Point4d var1) {
      super(var1);
   }

    public Point4d(Point4f var1) {
      super(var1);
   }

    public Point4d(Tuple4f var1) {
      super(var1);
   }

    public Point4d(Tuple4d var1) {
      super(var1);
   }

    public Point4d(Tuple3d var1) {
      super(var1.x, var1.y, var1.z, 1.0);
   }

    public Point4d() {
   }

    void set(Tuple3d var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.w = 1.0;
   }

    double distanceSquared(Point4d var1) {
    double var2 = this.x - var1.x;
    double var4 = this.y - var1.y;
    double var6 = this.z - var1.z;
    double var8 = this.w - var1.w;
      return var2 * var2 + var4 * var4 + var6 * var6 + var8 * var8;
   }

    double distance(Point4d var1) {
    double var2 = this.x - var1.x;
    double var4 = this.y - var1.y;
    double var6 = this.z - var1.z;
    double var8 = this.w - var1.w;
      return Math.sqrt(var2 * var2 + var4 * var4 + var6 * var6 + var8 * var8);
   }

    double distanceL1(Point4d var1) {
      return Math.abs(this.x - var1.x) + Math.abs(this.y - var1.y) + Math.abs(this.z - var1.z) + Math.abs(this.w - var1.w);
   }

    double distanceLinf(Point4d var1) {
    double var2 = Math.max(Math.abs(this.x - var1.x), Math.abs(this.y - var1.y));
    double var4 = Math.max(Math.abs(this.z - var1.z), Math.abs(this.w - var1.w));
      return Math.max(var2, var4);
   }

    void project(Point4d var1) {
    double var2 = 1.0 / var1.w;
      this.x = var1.x * var2;
      this.y = var1.y * var2;
      this.z = var1.z * var2;
      this.w = 1.0;
   }
}
} // namespace vecmath
} // namespace javax
