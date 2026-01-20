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


class Point3f : public Tuple3f {
public:
    static const long serialVersionUID = -8689337816398030143L;

    public Point3f(float var1, float var2, float var3) {
      super(var1, var2, var3);
   }

    public Point3f(float[] var1) {
      super(var1);
   }

    public Point3f(Point3f var1) {
      super(var1);
   }

    public Point3f(Point3d var1) {
      super(var1);
   }

    public Point3f(Tuple3f var1) {
      super(var1);
   }

    public Point3f(Tuple3d var1) {
      super(var1);
   }

    public Point3f() {
   }

    float distanceSquared(Point3f var1) {
    float var2 = this.x - var1.x;
    float var3 = this.y - var1.y;
    float var4 = this.z - var1.z;
      return var2 * var2 + var3 * var3 + var4 * var4;
   }

    float distance(Point3f var1) {
    float var2 = this.x - var1.x;
    float var3 = this.y - var1.y;
    float var4 = this.z - var1.z;
      return (float)Math.sqrt(var2 * var2 + var3 * var3 + var4 * var4);
   }

    float distanceL1(Point3f var1) {
      return Math.abs(this.x - var1.x) + Math.abs(this.y - var1.y) + Math.abs(this.z - var1.z);
   }

    float distanceLinf(Point3f var1) {
    float var2 = Math.max(Math.abs(this.x - var1.x), Math.abs(this.y - var1.y));
      return Math.max(var2, Math.abs(this.z - var1.z));
   }

    void project(Point4f var1) {
    float var2 = 1.0F / var1.w;
      this.x = var1.x * var2;
      this.y = var1.y * var2;
      this.z = var1.z * var2;
   }
}
} // namespace vecmath
} // namespace javax
