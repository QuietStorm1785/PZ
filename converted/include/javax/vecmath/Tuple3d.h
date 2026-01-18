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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Tuple3d {
public:
 static const long serialVersionUID = 5542096614926168415L;
 double x;
 double y;
 double z;

 public Tuple3d(double double0, double double1, double double2) {
 this->x = double0;
 this->y = double1;
 this->z = double2;
 }

 public Tuple3d(double[] doubles) {
 this->x = doubles[0];
 this->y = doubles[1];
 this->z = doubles[2];
 }

 public Tuple3d(Tuple3d tuple3d1) {
 this->x = tuple3d1.x;
 this->y = tuple3d1.y;
 this->z = tuple3d1.z;
 }

 public Tuple3d(Tuple3f tuple3f) {
 this->x = tuple3f.x;
 this->y = tuple3f.y;
 this->z = tuple3f.z;
 }

 public Tuple3d() {
 this->x = 0.0;
 this->y = 0.0;
 this->z = 0.0;
 }

 void set(double double0, double double1, double double2) {
 this->x = double0;
 this->y = double1;
 this->z = double2;
 }

 void set(double[] doubles) {
 this->x = doubles[0];
 this->y = doubles[1];
 this->z = doubles[2];
 }

 void set(Tuple3d tuple3d0) {
 this->x = tuple3d0.x;
 this->y = tuple3d0.y;
 this->z = tuple3d0.z;
 }

 void set(Tuple3f tuple3f) {
 this->x = tuple3f.x;
 this->y = tuple3f.y;
 this->z = tuple3f.z;
 }

 void get(double[] doubles) {
 doubles[0] = this->x;
 doubles[1] = this->y;
 doubles[2] = this->z;
 }

 void get(Tuple3d tuple3d1) {
 tuple3d1.x = this->x;
 tuple3d1.y = this->y;
 tuple3d1.z = this->z;
 }

 void add(Tuple3d tuple3d1, Tuple3d tuple3d0) {
 this->x = tuple3d1.x + tuple3d0.x;
 this->y = tuple3d1.y + tuple3d0.y;
 this->z = tuple3d1.z + tuple3d0.z;
 }

 void add(Tuple3d tuple3d0) {
 this->x = this->x + tuple3d0.x;
 this->y = this->y + tuple3d0.y;
 this->z = this->z + tuple3d0.z;
 }

 void sub(Tuple3d tuple3d1, Tuple3d tuple3d0) {
 this->x = tuple3d1.x - tuple3d0.x;
 this->y = tuple3d1.y - tuple3d0.y;
 this->z = tuple3d1.z - tuple3d0.z;
 }

 void sub(Tuple3d tuple3d0) {
 this->x = this->x - tuple3d0.x;
 this->y = this->y - tuple3d0.y;
 this->z = this->z - tuple3d0.z;
 }

 void negate(Tuple3d tuple3d0) {
 this->x = -tuple3d0.x;
 this->y = -tuple3d0.y;
 this->z = -tuple3d0.z;
 }

 void negate() {
 this->x = -this->x;
 this->y = -this->y;
 this->z = -this->z;
 }

 void scale(double double0, Tuple3d tuple3d0) {
 this->x = double0 * tuple3d0.x;
 this->y = double0 * tuple3d0.y;
 this->z = double0 * tuple3d0.z;
 }

 void scale(double double0) {
 this->x *= double0;
 this->y *= double0;
 this->z *= double0;
 }

 void scaleAdd(double double0, Tuple3d tuple3d1, Tuple3d tuple3d0) {
 this->x = double0 * tuple3d1.x + tuple3d0.x;
 this->y = double0 * tuple3d1.y + tuple3d0.y;
 this->z = double0 * tuple3d1.z + tuple3d0.z;
 }

 /** @deprecated */
 void scaleAdd(double double0, Tuple3f tuple3f) {
 this->scaleAdd(double0, new Point3d(tuple3f);
 }

 void scaleAdd(double double0, Tuple3d tuple3d0) {
 this->x = double0 * this->x + tuple3d0.x;
 this->y = double0 * this->y + tuple3d0.y;
 this->z = double0 * this->z + tuple3d0.z;
 }

 std::string toString() {
 return "(" + this->x + ", " + this->y + ", " + this->z + ")";
 }

 int hashCode() {
 long long0 = 1L;
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->x);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->y);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->z);
 return (int)(long0 ^ long0 >> 32);
 }

 bool equals(Tuple3d tuple3d0) {
 try {
 return this->x == tuple3d0.x && this->y == tuple3d0.y && this->z == tuple3d0.z;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }

 bool equals(void* object) {
 try {
 Tuple3d tuple3d0 = (Tuple3d)object;
 return this->x == tuple3d0.x && this->y == tuple3d0.y && this->z == tuple3d0.z;
 } catch (ClassCastException classCastException) {
 return false;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }

 bool epsilonEquals(Tuple3d tuple3d0, double double1) {
 double double0 = this->x - tuple3d0.x;
 if (Double.isNaN(double0) {
 return false;
 } else if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->y - tuple3d0.y;
 if (Double.isNaN(double0) {
 return false;
 } else if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->z - tuple3d0.z;
 return Double.isNaN(double0) ? false : !((double0 < 0.0 ? -double0 : double0) > double1);
 }
 }
 }

 /** @deprecated */
 void clamp(float float1, float float0, Tuple3d tuple3d1) {
 this->clamp((double)float1, (double)float0, tuple3d1);
 }

 void clamp(double double1, double double0, Tuple3d tuple3d0) {
 if (tuple3d0.x > double0) {
 this->x = double0;
 } else if (tuple3d0.x < double1) {
 this->x = double1;
 } else {
 this->x = tuple3d0.x;
 }

 if (tuple3d0.y > double0) {
 this->y = double0;
 } else if (tuple3d0.y < double1) {
 this->y = double1;
 } else {
 this->y = tuple3d0.y;
 }

 if (tuple3d0.z > double0) {
 this->z = double0;
 } else if (tuple3d0.z < double1) {
 this->z = double1;
 } else {
 this->z = tuple3d0.z;
 }
 }

 /** @deprecated */
 void clampMin(float float0, Tuple3d tuple3d1) {
 this->clampMin((double)float0, tuple3d1);
 }

 void clampMin(double double0, Tuple3d tuple3d0) {
 if (tuple3d0.x < double0) {
 this->x = double0;
 } else {
 this->x = tuple3d0.x;
 }

 if (tuple3d0.y < double0) {
 this->y = double0;
 } else {
 this->y = tuple3d0.y;
 }

 if (tuple3d0.z < double0) {
 this->z = double0;
 } else {
 this->z = tuple3d0.z;
 }
 }

 /** @deprecated */
 void clampMax(float float0, Tuple3d tuple3d1) {
 this->clampMax((double)float0, tuple3d1);
 }

 void clampMax(double double0, Tuple3d tuple3d0) {
 if (tuple3d0.x > double0) {
 this->x = double0;
 } else {
 this->x = tuple3d0.x;
 }

 if (tuple3d0.y > double0) {
 this->y = double0;
 } else {
 this->y = tuple3d0.y;
 }

 if (tuple3d0.z > double0) {
 this->z = double0;
 } else {
 this->z = tuple3d0.z;
 }
 }

 void absolute(Tuple3d tuple3d0) {
 this->x = Math.abs(tuple3d0.x);
 this->y = Math.abs(tuple3d0.y);
 this->z = Math.abs(tuple3d0.z);
 }

 /** @deprecated */
 void clamp(float float1, float float0) {
 this->clamp((double)float1, (double)float0);
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

 if (this->z > double0) {
 this->z = double0;
 } else if (this->z < double1) {
 this->z = double1;
 }
 }

 /** @deprecated */
 void clampMin(float float0) {
 this->clampMin((double)float0);
 }

 void clampMin(double double0) {
 if (this->x < double0) {
 this->x = double0;
 }

 if (this->y < double0) {
 this->y = double0;
 }

 if (this->z < double0) {
 this->z = double0;
 }
 }

 /** @deprecated */
 void clampMax(float float0) {
 this->clampMax((double)float0);
 }

 void clampMax(double double0) {
 if (this->x > double0) {
 this->x = double0;
 }

 if (this->y > double0) {
 this->y = double0;
 }

 if (this->z > double0) {
 this->z = double0;
 }
 }

 void absolute() {
 this->x = Math.abs(this->x);
 this->y = Math.abs(this->y);
 this->z = Math.abs(this->z);
 }

 /** @deprecated */
 void interpolate(Tuple3d tuple3d1, Tuple3d tuple3d2, float float0) {
 this->interpolate(tuple3d1, tuple3d2, (double)float0);
 }

 void interpolate(Tuple3d tuple3d1, Tuple3d tuple3d0, double double0) {
 this->x = (1.0 - double0) * tuple3d1.x + double0 * tuple3d0.x;
 this->y = (1.0 - double0) * tuple3d1.y + double0 * tuple3d0.y;
 this->z = (1.0 - double0) * tuple3d1.z + double0 * tuple3d0.z;
 }

 /** @deprecated */
 void interpolate(Tuple3d tuple3d1, float float0) {
 this->interpolate(tuple3d1, (double)float0);
 }

 void interpolate(Tuple3d tuple3d0, double double0) {
 this->x = (1.0 - double0) * this->x + double0 * tuple3d0.x;
 this->y = (1.0 - double0) * this->y + double0 * tuple3d0.y;
 this->z = (1.0 - double0) * this->z + double0 * tuple3d0.z;
 }

 void* clone() {
 try {
 return super.clone();
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<InternalError>();
 }
 }

 double getX() {
 return this->x;
 }

 void setX(double double0) {
 this->x = double0;
 }

 double getY() {
 return this->y;
 }

 void setY(double double0) {
 this->y = double0;
 }

 double getZ() {
 return this->z;
 }

 void setZ(double double0) {
 this->z = double0;
 }
}
} // namespace vecmath
} // namespace javax
