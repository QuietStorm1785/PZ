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


class Point2d : public Tuple2d {
public:
    static const long serialVersionUID = 1133748791492571954L;

    public Point2d(double var1, double var3) {
      super(var1, var3);
   }

    public Point2d(double[] var1) {
      super(var1);
   }

    public Point2d(Point2d var1) {
      super(var1);
   }

    public Point2d(Point2f var1) {
      super(var1);
   }

    public Point2d(Tuple2d var1) {
      super(var1);
   }

    public Point2d(Tuple2f var1) {
      super(var1);
   }

    public Point2d() {
   }

    double distanceSquared(Point2d var1) {
    double var2 = this.x - var1.x;
    double var4 = this.y - var1.y;
      return var2 * var2 + var4 * var4;
   }

    double distance(Point2d var1) {
    double var2 = this.x - var1.x;
    double var4 = this.y - var1.y;
      return Math.sqrt(var2 * var2 + var4 * var4);
   }

    double distanceL1(Point2d var1) {
      return Math.abs(this.x - var1.x) + Math.abs(this.y - var1.y);
   }

    double distanceLinf(Point2d var1) {
      return Math.max(Math.abs(this.x - var1.x), Math.abs(this.y - var1.y));
   }
}
} // namespace vecmath
} // namespace javax
