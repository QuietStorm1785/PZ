#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Tuple2d {
public:
 static const long serialVersionUID = 6205762482756093838L;
 double x;
 double y;

public
 Tuple2d(double double0, double double1) {
 this->x = double0;
 this->y = double1;
 }

public
 Tuple2d(double[] doubles) {
 this->x = doubles[0];
 this->y = doubles[1];
 }

public
 Tuple2d(Tuple2d tuple2d1) {
 this->x = tuple2d1.x;
 this->y = tuple2d1.y;
 }

public
 Tuple2d(Tuple2f tuple2f) {
 this->x = tuple2f.x;
 this->y = tuple2f.y;
 }

public
 Tuple2d() {
 this->x = 0.0;
 this->y = 0.0;
 }

 void set(double double0, double double1) {
 this->x = double0;
 this->y = double1;
 }

 void set(double[] doubles) {
 this->x = doubles[0];
 this->y = doubles[1];
 }

 void set(Tuple2d tuple2d0) {
 this->x = tuple2d0.x;
 this->y = tuple2d0.y;
 }

 void set(Tuple2f tuple2f) {
 this->x = tuple2f.x;
 this->y = tuple2f.y;
 }

 void get(double[] doubles) {
 doubles[0] = this->x;
 doubles[1] = this->y;
 }

 void add(Tuple2d tuple2d1, Tuple2d tuple2d0) {
 this->x = tuple2d1.x + tuple2d0.x;
 this->y = tuple2d1.y + tuple2d0.y;
 }

 void add(Tuple2d tuple2d0) {
 this->x = this->x + tuple2d0.x;
 this->y = this->y + tuple2d0.y;
 }

 void sub(Tuple2d tuple2d1, Tuple2d tuple2d0) {
 this->x = tuple2d1.x - tuple2d0.x;
 this->y = tuple2d1.y - tuple2d0.y;
 }

 void sub(Tuple2d tuple2d0) {
 this->x = this->x - tuple2d0.x;
 this->y = this->y - tuple2d0.y;
 }

 void negate(Tuple2d tuple2d0) {
 this->x = -tuple2d0.x;
 this->y = -tuple2d0.y;
 }

 void negate() {
 this->x = -this->x;
 this->y = -this->y;
 }

 void scale(double double0, Tuple2d tuple2d0) {
 this->x = double0 * tuple2d0.x;
 this->y = double0 * tuple2d0.y;
 }

 void scale(double double0) {
 this->x *= double0;
 this->y *= double0;
 }

 void scaleAdd(double double0, Tuple2d tuple2d1, Tuple2d tuple2d0) {
 this->x = double0 * tuple2d1.x + tuple2d0.x;
 this->y = double0 * tuple2d1.y + tuple2d0.y;
 }

 void scaleAdd(double double0, Tuple2d tuple2d0) {
 this->x = double0 * this->x + tuple2d0.x;
 this->y = double0 * this->y + tuple2d0.y;
 }

 int hashCode() {
 long long0 = 1L;
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->x);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->y);
 return (int)(long0 ^ long0 >> 32);
 }

 bool equals(Tuple2d tuple2d0) {
 try {
 return this->x == tuple2d0.x && this->y == tuple2d0.y;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }

 bool equals(void *object) {
 try {
 Tuple2d tuple2d0 = (Tuple2d)object;
 return this->x == tuple2d0.x && this->y == tuple2d0.y;
 } catch (NullPointerException nullPointerException) {
 return false;
 } catch (ClassCastException classCastException) {
 return false;
 }
 }

 bool epsilonEquals(Tuple2d tuple2d0, double double1) {
 double double0 = this->x - tuple2d0.x;
 if (Double.isNaN(double0) {
 return false;
 } else if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->y - tuple2d0.y;
 return Double.isNaN(double0)
 ? false
 : !((double0 < 0.0 ? -double0 : double0) > double1);
 }
 }

 std::string toString() { return "(" + this->x + ", " + this->y + ")"; }

 void clamp(double double1, double double0, Tuple2d tuple2d0) {
 if (tuple2d0.x > double0) {
 this->x = double0;
 } else if (tuple2d0.x < double1) {
 this->x = double1;
 } else {
 this->x = tuple2d0.x;
 }

 if (tuple2d0.y > double0) {
 this->y = double0;
 } else if (tuple2d0.y < double1) {
 this->y = double1;
 } else {
 this->y = tuple2d0.y;
 }
 }

 void clampMin(double double0, Tuple2d tuple2d0) {
 if (tuple2d0.x < double0) {
 this->x = double0;
 } else {
 this->x = tuple2d0.x;
 }

 if (tuple2d0.y < double0) {
 this->y = double0;
 } else {
 this->y = tuple2d0.y;
 }
 }

 void clampMax(double double0, Tuple2d tuple2d0) {
 if (tuple2d0.x > double0) {
 this->x = double0;
 } else {
 this->x = tuple2d0.x;
 }

 if (tuple2d0.y > double0) {
 this->y = double0;
 } else {
 this->y = tuple2d0.y;
 }
 }

 void absolute(Tuple2d tuple2d0) {
 this->x = Math.abs(tuple2d0.x);
 this->y = Math.abs(tuple2d0.y);
 }

 void clamp(double double1, double double0) {
 if (this->x > double0) {
 this->x = double0;
 } else if (this->x < double1) {
 this->x = double1;
 }

 if (this->y > double0) {
 this->y = double0;
 } else if (this->y < double1) {
 this->y = double1;
 }
 }

 void clampMin(double double0) {
 if (this->x < double0) {
 this->x = double0;
 }

 if (this->y < double0) {
 this->y = double0;
 }
 }

 void clampMax(double double0) {
 if (this->x > double0) {
 this->x = double0;
 }

 if (this->y > double0) {
 this->y = double0;
 }
 }

 void absolute() {
 this->x = Math.abs(this->x);
 this->y = Math.abs(this->y);
 }

 void interpolate(Tuple2d tuple2d1, Tuple2d tuple2d0, double double0) {
 this->x = (1.0 - double0) * tuple2d1.x + double0 * tuple2d0.x;
 this->y = (1.0 - double0) * tuple2d1.y + double0 * tuple2d0.y;
 }

 void interpolate(Tuple2d tuple2d0, double double0) {
 this->x = (1.0 - double0) * this->x + double0 * tuple2d0.x;
 this->y = (1.0 - double0) * this->y + double0 * tuple2d0.y;
 }

 void *clone() {
 try {
 return super.clone();
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<InternalError>();
 }
 }

 double getX() { return this->x; }

 void setX(double double0) { this->x = double0; }

 double getY() { return this->y; }

 void setY(double double0) { this->y = double0; }
}
} // namespace vecmath
} // namespace javax
