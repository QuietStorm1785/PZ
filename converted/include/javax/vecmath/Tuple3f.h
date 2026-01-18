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


class Tuple3f {
public:
 static const long serialVersionUID = 5019834619484343712L;
 float x;
 float y;
 float z;

 public Tuple3f(float float0, float float1, float float2) {
 this->x = float0;
 this->y = float1;
 this->z = float2;
 }

 public Tuple3f(float[] floats) {
 this->x = floats[0];
 this->y = floats[1];
 this->z = floats[2];
 }

 public Tuple3f(Tuple3f tuple3f1) {
 this->x = tuple3f1.x;
 this->y = tuple3f1.y;
 this->z = tuple3f1.z;
 }

 public Tuple3f(Tuple3d tuple3d) {
 this->x = (float)tuple3d.x;
 this->y = (float)tuple3d.y;
 this->z = (float)tuple3d.z;
 }

 public Tuple3f() {
 this->x = 0.0F;
 this->y = 0.0F;
 this->z = 0.0F;
 }

 std::string toString() {
 return "(" + this->x + ", " + this->y + ", " + this->z + ")";
 }

 void set(float float0, float float1, float float2) {
 this->x = float0;
 this->y = float1;
 this->z = float2;
 }

 void set(float[] floats) {
 this->x = floats[0];
 this->y = floats[1];
 this->z = floats[2];
 }

 void set(Tuple3f tuple3f0) {
 this->x = tuple3f0.x;
 this->y = tuple3f0.y;
 this->z = tuple3f0.z;
 }

 void set(Tuple3d tuple3d) {
 this->x = (float)tuple3d.x;
 this->y = (float)tuple3d.y;
 this->z = (float)tuple3d.z;
 }

 void get(float[] floats) {
 floats[0] = this->x;
 floats[1] = this->y;
 floats[2] = this->z;
 }

 void get(Tuple3f tuple3f1) {
 tuple3f1.x = this->x;
 tuple3f1.y = this->y;
 tuple3f1.z = this->z;
 }

 void add(Tuple3f tuple3f1, Tuple3f tuple3f0) {
 this->x = tuple3f1.x + tuple3f0.x;
 this->y = tuple3f1.y + tuple3f0.y;
 this->z = tuple3f1.z + tuple3f0.z;
 }

 void add(Tuple3f tuple3f0) {
 this->x = this->x + tuple3f0.x;
 this->y = this->y + tuple3f0.y;
 this->z = this->z + tuple3f0.z;
 }

 void sub(Tuple3f tuple3f1, Tuple3f tuple3f0) {
 this->x = tuple3f1.x - tuple3f0.x;
 this->y = tuple3f1.y - tuple3f0.y;
 this->z = tuple3f1.z - tuple3f0.z;
 }

 void sub(Tuple3f tuple3f0) {
 this->x = this->x - tuple3f0.x;
 this->y = this->y - tuple3f0.y;
 this->z = this->z - tuple3f0.z;
 }

 void negate(Tuple3f tuple3f0) {
 this->x = -tuple3f0.x;
 this->y = -tuple3f0.y;
 this->z = -tuple3f0.z;
 }

 void negate() {
 this->x = -this->x;
 this->y = -this->y;
 this->z = -this->z;
 }

 void scale(float float0, Tuple3f tuple3f0) {
 this->x = float0 * tuple3f0.x;
 this->y = float0 * tuple3f0.y;
 this->z = float0 * tuple3f0.z;
 }

 void scale(float float0) {
 this->x *= float0;
 this->y *= float0;
 this->z *= float0;
 }

 void scaleAdd(float float0, Tuple3f tuple3f1, Tuple3f tuple3f0) {
 this->x = float0 * tuple3f1.x + tuple3f0.x;
 this->y = float0 * tuple3f1.y + tuple3f0.y;
 this->z = float0 * tuple3f1.z + tuple3f0.z;
 }

 void scaleAdd(float float0, Tuple3f tuple3f0) {
 this->x = float0 * this->x + tuple3f0.x;
 this->y = float0 * this->y + tuple3f0.y;
 this->z = float0 * this->z + tuple3f0.z;
 }

 bool equals(Tuple3f tuple3f0) {
 try {
 return this->x == tuple3f0.x && this->y == tuple3f0.y && this->z == tuple3f0.z;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }

 bool equals(void* object) {
 try {
 Tuple3f tuple3f0 = (Tuple3f)object;
 return this->x == tuple3f0.x && this->y == tuple3f0.y && this->z == tuple3f0.z;
 } catch (NullPointerException nullPointerException) {
 return false;
 } catch (ClassCastException classCastException) {
 return false;
 }
 }

 bool epsilonEquals(Tuple3f tuple3f0, float float1) {
 float float0 = this->x - tuple3f0.x;
 if (Float.isNaN(float0) {
 return false;
 } else if ((float0 < 0.0F ? -float0 : float0) > float1) {
 return false;
 } else {
 float0 = this->y - tuple3f0.y;
 if (Float.isNaN(float0) {
 return false;
 } else if ((float0 < 0.0F ? -float0 : float0) > float1) {
 return false;
 } else {
 float0 = this->z - tuple3f0.z;
 return Float.isNaN(float0) ? false : !((float0 < 0.0F ? -float0 : float0) > float1);
 }
 }
 }

 int hashCode() {
 long long0 = 1L;
 long0 = 31L * long0 + VecMathUtil.floatToIntBits(this->x);
 long0 = 31L * long0 + VecMathUtil.floatToIntBits(this->y);
 long0 = 31L * long0 + VecMathUtil.floatToIntBits(this->z);
 return (int)(long0 ^ long0 >> 32);
 }

 void clamp(float float1, float float0, Tuple3f tuple3f0) {
 if (tuple3f0.x > float0) {
 this->x = float0;
 } else if (tuple3f0.x < float1) {
 this->x = float1;
 } else {
 this->x = tuple3f0.x;
 }

 if (tuple3f0.y > float0) {
 this->y = float0;
 } else if (tuple3f0.y < float1) {
 this->y = float1;
 } else {
 this->y = tuple3f0.y;
 }

 if (tuple3f0.z > float0) {
 this->z = float0;
 } else if (tuple3f0.z < float1) {
 this->z = float1;
 } else {
 this->z = tuple3f0.z;
 }
 }

 void clampMin(float float0, Tuple3f tuple3f0) {
 if (tuple3f0.x < float0) {
 this->x = float0;
 } else {
 this->x = tuple3f0.x;
 }

 if (tuple3f0.y < float0) {
 this->y = float0;
 } else {
 this->y = tuple3f0.y;
 }

 if (tuple3f0.z < float0) {
 this->z = float0;
 } else {
 this->z = tuple3f0.z;
 }
 }

 void clampMax(float float0, Tuple3f tuple3f0) {
 if (tuple3f0.x > float0) {
 this->x = float0;
 } else {
 this->x = tuple3f0.x;
 }

 if (tuple3f0.y > float0) {
 this->y = float0;
 } else {
 this->y = tuple3f0.y;
 }

 if (tuple3f0.z > float0) {
 this->z = float0;
 } else {
 this->z = tuple3f0.z;
 }
 }

 void absolute(Tuple3f tuple3f0) {
 this->x = Math.abs(tuple3f0.x);
 this->y = Math.abs(tuple3f0.y);
 this->z = Math.abs(tuple3f0.z);
 }

 void clamp(float float1, float float0) {
 if (this->x > float0) {
 this->x = float0;
 } else if (this->x < float1) {
 this->x = float1;
 }

 if (this->y > float0) {
 this->y = float0;
 } else if (this->y < float1) {
 this->y = float1;
 }

 if (this->z > float0) {
 this->z = float0;
 } else if (this->z < float1) {
 this->z = float1;
 }
 }

 void clampMin(float float0) {
 if (this->x < float0) {
 this->x = float0;
 }

 if (this->y < float0) {
 this->y = float0;
 }

 if (this->z < float0) {
 this->z = float0;
 }
 }

 void clampMax(float float0) {
 if (this->x > float0) {
 this->x = float0;
 }

 if (this->y > float0) {
 this->y = float0;
 }

 if (this->z > float0) {
 this->z = float0;
 }
 }

 void absolute() {
 this->x = Math.abs(this->x);
 this->y = Math.abs(this->y);
 this->z = Math.abs(this->z);
 }

 void interpolate(Tuple3f tuple3f1, Tuple3f tuple3f0, float float0) {
 this->x = (1.0F - float0) * tuple3f1.x + float0 * tuple3f0.x;
 this->y = (1.0F - float0) * tuple3f1.y + float0 * tuple3f0.y;
 this->z = (1.0F - float0) * tuple3f1.z + float0 * tuple3f0.z;
 }

 void interpolate(Tuple3f tuple3f0, float float0) {
 this->x = (1.0F - float0) * this->x + float0 * tuple3f0.x;
 this->y = (1.0F - float0) * this->y + float0 * tuple3f0.y;
 this->z = (1.0F - float0) * this->z + float0 * tuple3f0.z;
 }

 void* clone() {
 try {
 return super.clone();
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<InternalError>();
 }
 }

 float getX() {
 return this->x;
 }

 void setX(float float0) {
 this->x = float0;
 }

 float getY() {
 return this->y;
 }

 void setY(float float0) {
 this->y = float0;
 }

 float getZ() {
 return this->z;
 }

 void setZ(float float0) {
 this->z = float0;
 }
}
} // namespace vecmath
} // namespace javax
