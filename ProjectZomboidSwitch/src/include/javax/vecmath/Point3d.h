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


class Point3d : public Tuple3d {
public:
    static const long serialVersionUID = 5718062286069042927L;

    public Point3d(double var1, double var3, double var5) {
      super(var1, var3, var5);
   }

    public Point3d(double[] var1) {
      super(var1);
   }

    public Point3d(Point3d var1) {
      super(var1);
   }

    public Point3d(Point3f var1) {
      super(var1);
   }

    public Point3d(Tuple3f var1) {
      super(var1);
   }

    public Point3d(Tuple3d var1) {
      super(var1);
   }

    public Point3d() {
   }

    double distanceSquared(Point3d var1) {
    double var2 = this.x - var1.x;
    double var4 = this.y - var1.y;
    double var6 = this.z - var1.z;
      return var2 * var2 + var4 * var4 + var6 * var6;
   }

    double distance(Point3d var1) {
    double var2 = this.x - var1.x;
    double var4 = this.y - var1.y;
    double var6 = this.z - var1.z;
      return Math.sqrt(var2 * var2 + var4 * var4 + var6 * var6);
   }

    double distanceL1(Point3d var1) {
      return Math.abs(this.x - var1.x) + Math.abs(this.y - var1.y) + Math.abs(this.z - var1.z);
   }

    double distanceLinf(Point3d var1) {
    double var2 = Math.max(Math.abs(this.x - var1.x), Math.abs(this.y - var1.y));
      return Math.max(var2, Math.abs(this.z - var1.z));
   }

    void project(Point4d var1) {
    double var2 = 1.0 / var1.w;
      this.x = var1.x * var2;
      this.y = var1.y * var2;
      this.z = var1.z * var2;
   }
}
} // namespace vecmath
} // namespace javax
