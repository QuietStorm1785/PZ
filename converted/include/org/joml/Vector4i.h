#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/NumberFormat.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Vector4i {
public:
 static const long serialVersionUID = 1L;
 int x;
 int y;
 int z;
 int w;

 public Vector4i() {
 this->w = 1;
 }

 public Vector4i(Vector4ic arg0) {
 this->x = arg0.x();
 this->y = arg0.y();
 this->z = arg0.z();
 this->w = arg0.w();
 }

 public Vector4i(Vector3ic arg0, int arg1) {
 this->x = arg0.x();
 this->y = arg0.y();
 this->z = arg0.z();
 this->w = arg1;
 }

 public Vector4i(Vector2ic arg0, int arg1, int arg2) {
 this->x = arg0.x();
 this->y = arg0.y();
 this->z = arg1;
 this->w = arg2;
 }

 public Vector4i(Vector3fc arg0, float arg1, int arg2) {
 this->x = Math.roundUsing(arg0.x(), arg2);
 this->y = Math.roundUsing(arg0.y(), arg2);
 this->z = Math.roundUsing(arg0.z(), arg2);
 arg1 = Math.roundUsing(arg1, arg2);
 }

 public Vector4i(Vector4fc arg0, int arg1) {
 this->x = Math.roundUsing(arg0.x(), arg1);
 this->y = Math.roundUsing(arg0.y(), arg1);
 this->z = Math.roundUsing(arg0.z(), arg1);
 this->w = Math.roundUsing(arg0.w(), arg1);
 }

 public Vector4i(Vector4dc arg0, int arg1) {
 this->x = Math.roundUsing(arg0.x(), arg1);
 this->y = Math.roundUsing(arg0.y(), arg1);
 this->z = Math.roundUsing(arg0.z(), arg1);
 this->w = Math.roundUsing(arg0.w(), arg1);
 }

 public Vector4i(int arg0) {
 this->x = arg0;
 this->y = arg0;
 this->z = arg0;
 this->w = arg0;
 }

 public Vector4i(int arg0, int arg1, int arg2, int arg3) {
 this->x = arg0;
 this->y = arg1;
 this->z = arg2;
 this->w = arg3;
 }

 public Vector4i(int[] arg0) {
 this->x = arg0[0];
 this->y = arg0[1];
 this->z = arg0[2];
 this->w = arg0[3];
 }

 public Vector4i(ByteBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 }

 public Vector4i(int arg0, ByteBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 }

 public Vector4i(IntBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 }

 public Vector4i(int arg0, IntBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 }

 int x() {
 return this->x;
 }

 int y() {
 return this->y;
 }

 int z() {
 return this->z;
 }

 int w() {
 return this->w;
 }

 Vector4i set(Vector4ic arg0) {
 this->x = arg0.x();
 this->y = arg0.y();
 this->z = arg0.z();
 this->w = arg0.w();
 return this;
 }

 Vector4i set(Vector4dc arg0) {
 this->x = (int)arg0.x();
 this->y = (int)arg0.y();
 this->z = (int)arg0.z();
 this->w = (int)arg0.w();
 return this;
 }

 Vector4i set(Vector4dc arg0, int arg1) {
 this->x = Math.roundUsing(arg0.x(), arg1);
 this->y = Math.roundUsing(arg0.y(), arg1);
 this->z = Math.roundUsing(arg0.z(), arg1);
 this->w = Math.roundUsing(arg0.w(), arg1);
 return this;
 }

 Vector4i set(Vector4fc arg0, int arg1) {
 this->x = Math.roundUsing(arg0.x(), arg1);
 this->y = Math.roundUsing(arg0.y(), arg1);
 this->z = Math.roundUsing(arg0.z(), arg1);
 this->w = Math.roundUsing(arg0.w(), arg1);
 return this;
 }

 Vector4i set(Vector3ic arg0, int arg1) {
 this->x = arg0.x();
 this->y = arg0.y();
 this->z = arg0.z();
 this->w = arg1;
 return this;
 }

 Vector4i set(Vector2ic arg0, int arg1, int arg2) {
 this->x = arg0.x();
 this->y = arg0.y();
 this->z = arg1;
 this->w = arg2;
 return this;
 }

 Vector4i set(int arg0) {
 this->x = arg0;
 this->y = arg0;
 this->z = arg0;
 this->w = arg0;
 return this;
 }

 Vector4i set(int arg0, int arg1, int arg2, int arg3) {
 this->x = arg0;
 this->y = arg1;
 this->z = arg2;
 this->w = arg3;
 return this;
 }

 Vector4i set(int[] arg0) {
 this->x = arg0[0];
 this->y = arg0[1];
 this->z = arg0[2];
 this->w = arg0[2];
 return this;
 }

 Vector4i set(ByteBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 return this;
 }

 Vector4i set(int arg0, ByteBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 return this;
 }

 Vector4i set(IntBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 return this;
 }

 Vector4i set(int arg0, IntBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 return this;
 }

 Vector4i setFromAddress(long arg0) {
 if (Options.NO_UNSAFE) {
 throw UnsupportedOperationException("Not supported when using joml.nounsafe");
 } else {
 MemUtil.MemUtilUnsafe.get(this, arg0);
 return this;
 }
 }

 int get(int arg0) {
 switch (arg0) {
 case 0:
 return this->x;
 case 1:
 return this->y;
 case 2:
 return this->z;
 case 3:
 return this->w;
 default:
 throw std::make_unique<IllegalArgumentException>();
 }
 }

 int maxComponent() {
 int int0 = Math.abs(this->x);
 int int1 = Math.abs(this->y);
 int int2 = Math.abs(this->z);
 int int3 = Math.abs(this->w);
 if (int0 >= int1 && int0 >= int2 && int0 >= int3) {
 return 0;
 } else if (int1 >= int2 && int1 >= int3) {
 return 1;
 } else {
 return int2 >= int3 ? 2 : 3;
 }
 }

 int minComponent() {
 int int0 = Math.abs(this->x);
 int int1 = Math.abs(this->y);
 int int2 = Math.abs(this->z);
 int int3 = Math.abs(this->w);
 if (int0 < int1 && int0 < int2 && int0 < int3) {
 return 0;
 } else if (int1 < int2 && int1 < int3) {
 return 1;
 } else {
 return int2 < int3 ? 2 : 3;
 }
 }

 Vector4i setComponent(int arg0, int arg1) {
 switch (arg0) {
 case 0:
 this->x = arg1;
 break;
 case 1:
 this->y = arg1;
 break;
 case 2:
 this->z = arg1;
 break;
 case 3:
 this->w = arg1;
 break;
 default:
 throw std::make_unique<IllegalArgumentException>();
 }

 return this;
 }

 IntBuffer get(IntBuffer arg0) {
 MemUtil.INSTANCE.put(this, arg0.position(), arg0);
 return arg0;
 }

 IntBuffer get(int arg0, IntBuffer arg1) {
 MemUtil.INSTANCE.put(this, arg0, arg1);
 return arg1;
 }

 ByteBuffer get(ByteBuffer arg0) {
 MemUtil.INSTANCE.put(this, arg0.position(), arg0);
 return arg0;
 }

 ByteBuffer get(int arg0, ByteBuffer arg1) {
 MemUtil.INSTANCE.put(this, arg0, arg1);
 return arg1;
 }

 Vector4ic getToAddress(long arg0) {
 if (Options.NO_UNSAFE) {
 throw UnsupportedOperationException("Not supported when using joml.nounsafe");
 } else {
 MemUtil.MemUtilUnsafe.put(this, arg0);
 return this;
 }
 }

 Vector4i sub(Vector4ic arg0) {
 this->x = this->x - arg0.x();
 this->y = this->y - arg0.y();
 this->z = this->z - arg0.z();
 this->w = this->w - arg0.w();
 return this;
 }

 Vector4i sub(int arg0, int arg1, int arg2, int arg3) {
 this->x -= arg0;
 this->y -= arg1;
 this->z -= arg2;
 this->w -= arg3;
 return this;
 }

 Vector4i sub(Vector4ic arg0, Vector4i arg1) {
 arg1.x = this->x - arg0.x();
 arg1.y = this->y - arg0.y();
 arg1.z = this->z - arg0.z();
 arg1.w = this->w - arg0.w();
 return arg1;
 }

 Vector4i sub(int arg0, int arg1, int arg2, int arg3, Vector4i arg4) {
 arg4.x = this->x - arg0;
 arg4.y = this->y - arg1;
 arg4.z = this->z - arg2;
 arg4.w = this->w - arg3;
 return arg4;
 }

 Vector4i add(Vector4ic arg0) {
 this->x = this->x + arg0.x();
 this->y = this->y + arg0.y();
 this->z = this->z + arg0.z();
 this->w = this->w + arg0.w();
 return this;
 }

 Vector4i add(Vector4ic arg0, Vector4i arg1) {
 arg1.x = this->x + arg0.x();
 arg1.y = this->y + arg0.y();
 arg1.z = this->z + arg0.z();
 arg1.w = this->w + arg0.w();
 return arg1;
 }

 Vector4i add(int arg0, int arg1, int arg2, int arg3) {
 this->x += arg0;
 this->y += arg1;
 this->z += arg2;
 this->w += arg3;
 return this;
 }

 Vector4i add(int arg0, int arg1, int arg2, int arg3, Vector4i arg4) {
 arg4.x = this->x + arg0;
 arg4.y = this->y + arg1;
 arg4.z = this->z + arg2;
 arg4.w = this->w + arg3;
 return arg4;
 }

 Vector4i mul(Vector4ic arg0) {
 this->x = this->x * arg0.x();
 this->y = this->y * arg0.y();
 this->z = this->z * arg0.z();
 this->w = this->w * arg0.w();
 return this;
 }

 Vector4i mul(Vector4ic arg0, Vector4i arg1) {
 arg1.x = this->x * arg0.x();
 arg1.y = this->y * arg0.y();
 arg1.z = this->z * arg0.z();
 arg1.w = this->w * arg0.w();
 return arg1;
 }

 Vector4i div(Vector4ic arg0) {
 this->x = this->x / arg0.x();
 this->y = this->y / arg0.y();
 this->z = this->z / arg0.z();
 this->w = this->w / arg0.w();
 return this;
 }

 Vector4i div(Vector4ic arg0, Vector4i arg1) {
 arg1.x = this->x / arg0.x();
 arg1.y = this->y / arg0.y();
 arg1.z = this->z / arg0.z();
 arg1.w = this->w / arg0.w();
 return arg1;
 }

 Vector4i mul(int arg0) {
 this->x *= arg0;
 this->y *= arg0;
 this->z *= arg0;
 this->w *= arg0;
 return this;
 }

 Vector4i mul(int arg0, Vector4i arg1) {
 arg1.x = this->x * arg0;
 arg1.y = this->y * arg0;
 arg1.z = this->z * arg0;
 arg1.w = this->w * arg0;
 return arg1;
 }

 Vector4i div(float arg0) {
 float float0 = 1.0F / arg0;
 this->x = (int)(this->x * float0);
 this->y = (int)(this->y * float0);
 this->z = (int)(this->z * float0);
 this->w = (int)(this->w * float0);
 return this;
 }

 Vector4i div(float arg0, Vector4i arg1) {
 float float0 = 1.0F / arg0;
 arg1.x = (int)(this->x * float0);
 arg1.y = (int)(this->y * float0);
 arg1.z = (int)(this->z * float0);
 arg1.w = (int)(this->w * float0);
 return arg1;
 }

 Vector4i div(int arg0) {
 this->x /= arg0;
 this->y /= arg0;
 this->z /= arg0;
 this->w /= arg0;
 return this;
 }

 Vector4i div(int arg0, Vector4i arg1) {
 arg1.x = this->x / arg0;
 arg1.y = this->y / arg0;
 arg1.z = this->z / arg0;
 arg1.w = this->w / arg0;
 return arg1;
 }

 long lengthSquared() {
 return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
 }

 static long lengthSquared(int arg0, int arg1, int arg2, int arg3) {
 return arg0 * arg0 + arg1 * arg1 + arg2 * arg2 + arg3 * arg3;
 }

 double length() {
 return Math.sqrt((float)(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
 }

 static double length(int arg0, int arg1, int arg2, int arg3) {
 return Math.sqrt((float)(arg0 * arg0 + arg1 * arg1 + arg2 * arg2 + arg3 * arg3);
 }

 double distance(Vector4ic arg0) {
 int int0 = this->x - arg0.x();
 int int1 = this->y - arg0.y();
 int int2 = this->z - arg0.z();
 int int3 = this->w - arg0.w();
 return Math.sqrt(Math.fma((float)int0, (float)int0, Math.fma((float)int1, (float)int1, Math.fma((float)int2, (float)int2, (float)(int3 * int3));
 }

 double distance(int arg0, int arg1, int arg2, int arg3) {
 int int0 = this->x - arg0;
 int int1 = this->y - arg1;
 int int2 = this->z - arg2;
 int int3 = this->w - arg3;
 return Math.sqrt(Math.fma((float)int0, (float)int0, Math.fma((float)int1, (float)int1, Math.fma((float)int2, (float)int2, (float)(int3 * int3));
 }

 long gridDistance(Vector4ic arg0) {
 return Math.abs(arg0.x() - this->x()) + Math.abs(arg0.y() - this->y()) + Math.abs(arg0.z() - this->z()) + Math.abs(arg0.w() - this->w());
 }

 long gridDistance(int arg0, int arg1, int arg2, int arg3) {
 return Math.abs(arg0 - this->x()) + Math.abs(arg1 - this->y()) + Math.abs(arg2 - this->z()) + Math.abs(arg3 - this->w());
 }

 int distanceSquared(Vector4ic arg0) {
 int int0 = this->x - arg0.x();
 int int1 = this->y - arg0.y();
 int int2 = this->z - arg0.z();
 int int3 = this->w - arg0.w();
 return int0 * int0 + int1 * int1 + int2 * int2 + int3 * int3;
 }

 int distanceSquared(int arg0, int arg1, int arg2, int arg3) {
 int int0 = this->x - arg0;
 int int1 = this->y - arg1;
 int int2 = this->z - arg2;
 int int3 = this->w - arg3;
 return int0 * int0 + int1 * int1 + int2 * int2 + int3 * int3;
 }

 static double distance(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
 int int0 = arg0 - arg4;
 int int1 = arg1 - arg5;
 int int2 = arg2 - arg6;
 int int3 = arg3 - arg7;
 return Math.sqrt((float)(int0 * int0 + int1 * int1 + int2 * int2 + int3 * int3);
 }

 static long distanceSquared(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
 int int0 = arg0 - arg4;
 int int1 = arg1 - arg5;
 int int2 = arg2 - arg6;
 int int3 = arg3 - arg7;
 return int0 * int0 + int1 * int1 + int2 * int2 + int3 * int3;
 }

 int dot(Vector4ic arg0) {
 return this->x * arg0.x() + this->y * arg0.y() + this->z * arg0.z() + this->w * arg0.w();
 }

 Vector4i zero() {
 this->x = 0;
 this->y = 0;
 this->z = 0;
 this->w = 0;
 return this;
 }

 Vector4i negate() {
 this->x = -this->x;
 this->y = -this->y;
 this->z = -this->z;
 this->w = -this->w;
 return this;
 }

 Vector4i negate(Vector4i arg0) {
 arg0.x = -this->x;
 arg0.y = -this->y;
 arg0.z = -this->z;
 arg0.w = -this->w;
 return arg0;
 }

 std::string toString() {
 return Runtime.formatNumbers(this->toString(Options.NUMBER_FORMAT);
 }

 std::string toString(NumberFormat numberFormat) {
 return "("
 + numberFormat.format((long)this->x)
 + " "
 + numberFormat.format((long)this->y)
 + " "
 + numberFormat.format((long)this->z)
 + " "
 + numberFormat.format((long)this->w)
 + ")";
 }

 void writeExternal(ObjectOutput arg0) {
 arg0.writeInt(this->x);
 arg0.writeInt(this->y);
 arg0.writeInt(this->z);
 arg0.writeInt(this->w);
 }

 void readExternal(ObjectInput arg0) {
 this->x = arg0.readInt();
 this->y = arg0.readInt();
 this->z = arg0.readInt();
 this->w = arg0.readInt();
 }

 Vector4i min(Vector4ic arg0) {
 this->x = this->x < arg0.x() ? this->x : arg0.x();
 this->y = this->y < arg0.y() ? this->y : arg0.y();
 this->z = this->z < arg0.z() ? this->z : arg0.z();
 this->w = this->w < arg0.w() ? this->w : arg0.w();
 return this;
 }

 Vector4i min(Vector4ic arg0, Vector4i arg1) {
 arg1.x = this->x < arg0.x() ? this->x : arg0.x();
 arg1.y = this->y < arg0.y() ? this->y : arg0.y();
 arg1.z = this->z < arg0.z() ? this->z : arg0.z();
 arg1.w = this->w < arg0.w() ? this->w : arg0.w();
 return arg1;
 }

 Vector4i max(Vector4ic arg0) {
 this->x = this->x > arg0.x() ? this->x : arg0.x();
 this->y = this->y > arg0.y() ? this->y : arg0.y();
 this->z = this->z > arg0.z() ? this->z : arg0.z();
 this->w = this->w > arg0.w() ? this->w : arg0.w();
 return this;
 }

 Vector4i max(Vector4ic arg0, Vector4i arg1) {
 arg1.x = this->x > arg0.x() ? this->x : arg0.x();
 arg1.y = this->y > arg0.y() ? this->y : arg0.y();
 arg1.z = this->z > arg0.z() ? this->z : arg0.z();
 arg1.w = this->w > arg0.w() ? this->w : arg0.w();
 return arg1;
 }

 Vector4i absolute() {
 this->x = Math.abs(this->x);
 this->y = Math.abs(this->y);
 this->z = Math.abs(this->z);
 this->w = Math.abs(this->w);
 return this;
 }

 Vector4i absolute(Vector4i arg0) {
 arg0.x = Math.abs(this->x);
 arg0.y = Math.abs(this->y);
 arg0.z = Math.abs(this->z);
 arg0.w = Math.abs(this->w);
 return arg0;
 }

 int hashCode() {
 int int0 = 1;
 int0 = 31 * int0 + this->x;
 int0 = 31 * int0 + this->y;
 int0 = 31 * int0 + this->z;
 return 31 * int0 + this->w;
 }

 bool equals(void* arg0) {
 if (this == arg0) {
 return true;
 } else if (arg0.empty()) {
 return false;
 } else if (this->getClass() != arg0.getClass()) {
 return false;
 } else {
 Vector4i vector4i = (Vector4i)arg0;
 if (this->x != vector4i.x) {
 return false;
 } else if (this->y != vector4i.y) {
 return false;
 } else {
 return this->z != vector4i.z ? false : this->w == vector4i.w;
 }
 }
 }

 bool equals(int arg0, int arg1, int arg2, int arg3) {
 if (this->x != arg0) {
 return false;
 } else if (this->y != arg1) {
 return false;
 } else {
 return this->z != arg2 ? false : this->w == arg3;
 }
 }
}
} // namespace joml
} // namespace org
