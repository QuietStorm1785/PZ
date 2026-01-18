#pragma once
#include "java/text/NumberFormat.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Vector2f {
public:
 static const long serialVersionUID = 1L;
 float x;
 float y;

public
 Vector2f() {}

public
 Vector2f(float arg0) {
 this->x = arg0;
 this->y = arg0;
 }

public
 Vector2f(float arg0, float arg1) {
 this->x = arg0;
 this->y = arg1;
 }

public
 Vector2f(Vector2fc arg0) {
 this->x = arg0.x();
 this->y = arg0.y();
 }

public
 Vector2f(Vector2ic arg0) {
 this->x = arg0.x();
 this->y = arg0.y();
 }

public
 Vector2f(float[] arg0) {
 this->x = arg0[0];
 this->y = arg0[1];
 }

public
 Vector2f(ByteBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 }

public
 Vector2f(int arg0, ByteBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 }

public
 Vector2f(FloatBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 }

public
 Vector2f(int arg0, FloatBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 }

 float x() { return this->x; }

 float y() { return this->y; }

 Vector2f set(float arg0) {
 this->x = arg0;
 this->y = arg0;
 return this;
 }

 Vector2f set(float arg0, float arg1) {
 this->x = arg0;
 this->y = arg1;
 return this;
 }

 Vector2f set(double arg0) {
 this->x = (float)arg0;
 this->y = (float)arg0;
 return this;
 }

 Vector2f set(double arg0, double arg1) {
 this->x = (float)arg0;
 this->y = (float)arg1;
 return this;
 }

 Vector2f set(Vector2fc arg0) {
 this->x = arg0.x();
 this->y = arg0.y();
 return this;
 }

 Vector2f set(Vector2ic arg0) {
 this->x = arg0.x();
 this->y = arg0.y();
 return this;
 }

 Vector2f set(Vector2dc arg0) {
 this->x = (float)arg0.x();
 this->y = (float)arg0.y();
 return this;
 }

 Vector2f set(float[] arg0) {
 this->x = arg0[0];
 this->y = arg0[1];
 return this;
 }

 Vector2f set(ByteBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 return this;
 }

 Vector2f set(int arg0, ByteBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 return this;
 }

 Vector2f set(FloatBuffer arg0) {
 MemUtil.INSTANCE.get(this, arg0.position(), arg0);
 return this;
 }

 Vector2f set(int arg0, FloatBuffer arg1) {
 MemUtil.INSTANCE.get(this, arg0, arg1);
 return this;
 }

 Vector2f setFromAddress(long arg0) {
 if (Options.NO_UNSAFE) {
 throw UnsupportedOperationException(
 "Not supported when using joml.nounsafe");
 } else {
 MemUtil.MemUtilUnsafe.get(this, arg0);
 return this;
 }
 }

 float get(int arg0) {
 switch (arg0) {
 case 0:
 return this->x;
 case 1:
 return this->y;
 default:
 throw std::make_unique<IllegalArgumentException>();
 }
 }

 Vector2i get(int arg0, Vector2i arg1) {
 arg1.x = Math.roundUsing(this->x(), arg0);
 arg1.y = Math.roundUsing(this->y(), arg0);
 return arg1;
 }

 Vector2f get(Vector2f arg0) {
 arg0.x = this->x();
 arg0.y = this->y();
 return arg0;
 }

 Vector2d get(Vector2d arg0) {
 arg0.x = this->x();
 arg0.y = this->y();
 return arg0;
 }

 Vector2f setComponent(int arg0, float arg1) {
 switch (arg0) {
 case 0:
 this->x = arg1;
 break;
 case 1:
 this->y = arg1;
 break;
 default:
 throw std::make_unique<IllegalArgumentException>();
 }

 return this;
 }

 ByteBuffer get(ByteBuffer arg0) {
 MemUtil.INSTANCE.put(this, arg0.position(), arg0);
 return arg0;
 }

 ByteBuffer get(int arg0, ByteBuffer arg1) {
 MemUtil.INSTANCE.put(this, arg0, arg1);
 return arg1;
 }

 FloatBuffer get(FloatBuffer arg0) {
 MemUtil.INSTANCE.put(this, arg0.position(), arg0);
 return arg0;
 }

 FloatBuffer get(int arg0, FloatBuffer arg1) {
 MemUtil.INSTANCE.put(this, arg0, arg1);
 return arg1;
 }

 Vector2fc getToAddress(long arg0) {
 if (Options.NO_UNSAFE) {
 throw UnsupportedOperationException(
 "Not supported when using joml.nounsafe");
 } else {
 MemUtil.MemUtilUnsafe.put(this, arg0);
 return this;
 }
 }

 Vector2f perpendicular() {
 float float0 = this->y;
 this->y = this->x * -1.0F;
 this->x = float0;
 return this;
 }

 Vector2f sub(Vector2fc arg0) {
 this->x = this->x - arg0.x();
 this->y = this->y - arg0.y();
 return this;
 }

 Vector2f sub(Vector2fc arg0, Vector2f arg1) {
 arg1.x = this->x - arg0.x();
 arg1.y = this->y - arg0.y();
 return arg1;
 }

 Vector2f sub(float arg0, float arg1) {
 this->x -= arg0;
 this->y -= arg1;
 return this;
 }

 Vector2f sub(float arg0, float arg1, Vector2f arg2) {
 arg2.x = this->x - arg0;
 arg2.y = this->y - arg1;
 return arg2;
 }

 float dot(Vector2fc arg0) { return this->x * arg0.x() + this->y * arg0.y(); }

 float angle(Vector2fc arg0) {
 float float0 = this->x * arg0.x() + this->y * arg0.y();
 float float1 = this->x * arg0.y() - this->y * arg0.x();
 return Math.atan2(float1, float0);
 }

 float lengthSquared() { return this->x * this->x + this->y * this->y; }

 static float lengthSquared(float arg0, float arg1) {
 return arg0 * arg0 + arg1 * arg1;
 }

 float length() { return Math.sqrt(this->x * this->x + this->y * this->y); }

 static float length(float arg0, float arg1) {
 return Math.sqrt(arg0 * arg0 + arg1 * arg1);
 }

 float distance(Vector2fc arg0) {
 float float0 = this->x - arg0.x();
 float float1 = this->y - arg0.y();
 return Math.sqrt(float0 * float0 + float1 * float1);
 }

 float distanceSquared(Vector2fc arg0) {
 float float0 = this->x - arg0.x();
 float float1 = this->y - arg0.y();
 return float0 * float0 + float1 * float1;
 }

 float distance(float arg0, float arg1) {
 float float0 = this->x - arg0;
 float float1 = this->y - arg1;
 return Math.sqrt(float0 * float0 + float1 * float1);
 }

 float distanceSquared(float arg0, float arg1) {
 float float0 = this->x - arg0;
 float float1 = this->y - arg1;
 return float0 * float0 + float1 * float1;
 }

 static float distance(float arg0, float arg1, float arg2, float arg3) {
 float float0 = arg0 - arg2;
 float float1 = arg1 - arg3;
 return Math.sqrt(float0 * float0 + float1 * float1);
 }

 static float distanceSquared(float arg0, float arg1, float arg2, float arg3) {
 float float0 = arg0 - arg2;
 float float1 = arg1 - arg3;
 return float0 * float0 + float1 * float1;
 }

 Vector2f normalize() {
 float float0 = Math.invsqrt(this->x * this->x + this->y * this->y);
 this->x *= float0;
 this->y *= float0;
 return this;
 }

 Vector2f normalize(Vector2f arg0) {
 float float0 = Math.invsqrt(this->x * this->x + this->y * this->y);
 arg0.x = this->x * float0;
 arg0.y = this->y * float0;
 return arg0;
 }

 Vector2f normalize(float arg0) {
 float float0 = Math.invsqrt(this->x * this->x + this->y * this->y) * arg0;
 this->x *= float0;
 this->y *= float0;
 return this;
 }

 Vector2f normalize(float arg0, Vector2f arg1) {
 float float0 = Math.invsqrt(this->x * this->x + this->y * this->y) * arg0;
 arg1.x = this->x * float0;
 arg1.y = this->y * float0;
 return arg1;
 }

 Vector2f add(Vector2fc arg0) {
 this->x = this->x + arg0.x();
 this->y = this->y + arg0.y();
 return this;
 }

 Vector2f add(Vector2fc arg0, Vector2f arg1) {
 arg1.x = this->x + arg0.x();
 arg1.y = this->y + arg0.y();
 return arg1;
 }

 Vector2f add(float arg0, float arg1) { return this->add(arg0, arg1, this); }

 Vector2f add(float arg0, float arg1, Vector2f arg2) {
 arg2.x = this->x + arg0;
 arg2.y = this->y + arg1;
 return arg2;
 }

 Vector2f zero() {
 this->x = 0.0F;
 this->y = 0.0F;
 return this;
 }

 void writeExternal(ObjectOutput arg0) {
 arg0.writeFloat(this->x);
 arg0.writeFloat(this->y);
 }

 void readExternal(ObjectInput arg0) {
 this->x = arg0.readFloat();
 this->y = arg0.readFloat();
 }

 Vector2f negate() {
 this->x = -this->x;
 this->y = -this->y;
 return this;
 }

 Vector2f negate(Vector2f arg0) {
 arg0.x = -this->x;
 arg0.y = -this->y;
 return arg0;
 }

 Vector2f mul(float arg0) {
 this->x *= arg0;
 this->y *= arg0;
 return this;
 }

 Vector2f mul(float arg0, Vector2f arg1) {
 arg1.x = this->x * arg0;
 arg1.y = this->y * arg0;
 return arg1;
 }

 Vector2f mul(float arg0, float arg1) {
 this->x *= arg0;
 this->y *= arg1;
 return this;
 }

 Vector2f mul(float arg0, float arg1, Vector2f arg2) {
 arg2.x = this->x * arg0;
 arg2.y = this->y * arg1;
 return arg2;
 }

 Vector2f mul(Vector2fc arg0) {
 this->x = this->x * arg0.x();
 this->y = this->y * arg0.y();
 return this;
 }

 Vector2f mul(Vector2fc arg0, Vector2f arg1) {
 arg1.x = this->x * arg0.x();
 arg1.y = this->y * arg0.y();
 return arg1;
 }

 Vector2f div(Vector2fc arg0) {
 this->x = this->x / arg0.x();
 this->y = this->y / arg0.y();
 return this;
 }

 Vector2f div(Vector2fc arg0, Vector2f arg1) {
 arg1.x = this->x / arg0.x();
 arg1.y = this->y / arg0.y();
 return arg1;
 }

 Vector2f div(float arg0) {
 float float0 = 1.0F / arg0;
 this->x *= float0;
 this->y *= float0;
 return this;
 }

 Vector2f div(float arg0, Vector2f arg1) {
 float float0 = 1.0F / arg0;
 arg1.x = this->x * float0;
 arg1.y = this->y * float0;
 return arg1;
 }

 Vector2f div(float arg0, float arg1) {
 this->x /= arg0;
 this->y /= arg1;
 return this;
 }

 Vector2f div(float arg0, float arg1, Vector2f arg2) {
 arg2.x = this->x / arg0;
 arg2.y = this->y / arg1;
 return arg2;
 }

 Vector2f mul(Matrix2fc arg0) {
 float float0 = arg0.m00() * this->x + arg0.m10() * this->y;
 float float1 = arg0.m01() * this->x + arg0.m11() * this->y;
 this->x = float0;
 this->y = float1;
 return this;
 }

 Vector2f mul(Matrix2fc arg0, Vector2f arg1) {
 float float0 = arg0.m00() * this->x + arg0.m10() * this->y;
 float float1 = arg0.m01() * this->x + arg0.m11() * this->y;
 arg1.x = float0;
 arg1.y = float1;
 return arg1;
 }

 Vector2f mul(Matrix2dc arg0) {
 double double0 = arg0.m00() * this->x + arg0.m10() * this->y;
 double double1 = arg0.m01() * this->x + arg0.m11() * this->y;
 this->x = (float)double0;
 this->y = (float)double1;
 return this;
 }

 Vector2f mul(Matrix2dc arg0, Vector2f arg1) {
 double double0 = arg0.m00() * this->x + arg0.m10() * this->y;
 double double1 = arg0.m01() * this->x + arg0.m11() * this->y;
 arg1.x = (float)double0;
 arg1.y = (float)double1;
 return arg1;
 }

 Vector2f mulTranspose(Matrix2fc arg0) {
 float float0 = arg0.m00() * this->x + arg0.m01() * this->y;
 float float1 = arg0.m10() * this->x + arg0.m11() * this->y;
 this->x = float0;
 this->y = float1;
 return this;
 }

 Vector2f mulTranspose(Matrix2fc arg0, Vector2f arg1) {
 float float0 = arg0.m00() * this->x + arg0.m01() * this->y;
 float float1 = arg0.m10() * this->x + arg0.m11() * this->y;
 arg1.x = float0;
 arg1.y = float1;
 return arg1;
 }

 Vector2f mulPosition(Matrix3x2fc arg0) {
 this->x = arg0.m00() * this->x + arg0.m10() * this->y + arg0.m20();
 this->y = arg0.m01() * this->x + arg0.m11() * this->y + arg0.m21();
 return this;
 }

 Vector2f mulPosition(Matrix3x2fc arg0, Vector2f arg1) {
 arg1.x = arg0.m00() * this->x + arg0.m10() * this->y + arg0.m20();
 arg1.y = arg0.m01() * this->x + arg0.m11() * this->y + arg0.m21();
 return arg1;
 }

 Vector2f mulDirection(Matrix3x2fc arg0) {
 this->x = arg0.m00() * this->x + arg0.m10() * this->y;
 this->y = arg0.m01() * this->x + arg0.m11() * this->y;
 return this;
 }

 Vector2f mulDirection(Matrix3x2fc arg0, Vector2f arg1) {
 arg1.x = arg0.m00() * this->x + arg0.m10() * this->y;
 arg1.y = arg0.m01() * this->x + arg0.m11() * this->y;
 return arg1;
 }

 Vector2f lerp(Vector2fc arg0, float arg1) {
 this->x = this->x + (arg0.x() - this->x) * arg1;
 this->y = this->y + (arg0.y() - this->y) * arg1;
 return this;
 }

 Vector2f lerp(Vector2fc arg0, float arg1, Vector2f arg2) {
 arg2.x = this->x + (arg0.x() - this->x) * arg1;
 arg2.y = this->y + (arg0.y() - this->y) * arg1;
 return arg2;
 }

 int hashCode() {
 int int0 = 1;
 int0 = 31 * int0 + Float.floatToIntBits(this->x);
 return 31 * int0 + Float.floatToIntBits(this->y);
 }

 bool equals(void *arg0) {
 if (this == arg0) {
 return true;
 } else if (arg0.empty()) {
 return false;
 } else if (this->getClass() != arg0.getClass()) {
 return false;
 } else {
 Vector2f vector2f = (Vector2f)arg0;
 return Float.floatToIntBits(this->x) != Float.floatToIntBits(vector2f.x)
 ? false
 : Float.floatToIntBits(this->y) ==
 Float.floatToIntBits(vector2f.y);
 }
 }

 bool equals(Vector2fc arg0, float arg1) {
 if (this == arg0) {
 return true;
 } else if (arg0.empty()) {
 return false;
 } else if (!(dynamic_cast<Vector2fc*>(arg0) != nullptr) {
 return false;
 } else {
 return !Runtime == this->x, arg0.x(), arg1) ? false : Runtime == this->y, arg0.y(), arg1);
 }
 }

 bool equals(float arg0, float arg1) {
 return Float.floatToIntBits(this->x) != Float.floatToIntBits(arg0)
 ? false
 : Float.floatToIntBits(this->y) == Float.floatToIntBits(arg1);
 }

 std::string toString() {
 return Runtime.formatNumbers(this->toString(Options.NUMBER_FORMAT);
 }

 std::string toString(NumberFormat numberFormat) {
 return "(" + Runtime.format(this->x, numberFormat) + " " +
 Runtime.format(this->y, numberFormat) + ")";
 }

 Vector2f fma(Vector2fc arg0, Vector2fc arg1) {
 this->x = this->x + arg0.x() * arg1.x();
 this->y = this->y + arg0.y() * arg1.y();
 return this;
 }

 Vector2f fma(float arg0, Vector2fc arg1) {
 this->x = this->x + arg0 * arg1.x();
 this->y = this->y + arg0 * arg1.y();
 return this;
 }

 Vector2f fma(Vector2fc arg0, Vector2fc arg1, Vector2f arg2) {
 arg2.x = this->x + arg0.x() * arg1.x();
 arg2.y = this->y + arg0.y() * arg1.y();
 return arg2;
 }

 Vector2f fma(float arg0, Vector2fc arg1, Vector2f arg2) {
 arg2.x = this->x + arg0 * arg1.x();
 arg2.y = this->y + arg0 * arg1.y();
 return arg2;
 }

 Vector2f min(Vector2fc arg0) {
 this->x = this->x < arg0.x() ? this->x : arg0.x();
 this->y = this->y < arg0.y() ? this->y : arg0.y();
 return this;
 }

 Vector2f min(Vector2fc arg0, Vector2f arg1) {
 arg1.x = this->x < arg0.x() ? this->x : arg0.x();
 arg1.y = this->y < arg0.y() ? this->y : arg0.y();
 return arg1;
 }

 Vector2f max(Vector2fc arg0) {
 this->x = this->x > arg0.x() ? this->x : arg0.x();
 this->y = this->y > arg0.y() ? this->y : arg0.y();
 return this;
 }

 Vector2f max(Vector2fc arg0, Vector2f arg1) {
 arg1.x = this->x > arg0.x() ? this->x : arg0.x();
 arg1.y = this->y > arg0.y() ? this->y : arg0.y();
 return arg1;
 }

 int maxComponent() {
 float float0 = Math.abs(this->x);
 float float1 = Math.abs(this->y);
 return float0 >= float1 ? 0 : 1;
 }

 int minComponent() {
 float float0 = Math.abs(this->x);
 float float1 = Math.abs(this->y);
 return float0 < float1 ? 0 : 1;
 }

 Vector2f floor() {
 this->x = Math.floor(this->x);
 this->y = Math.floor(this->y);
 return this;
 }

 Vector2f floor(Vector2f arg0) {
 arg0.x = Math.floor(this->x);
 arg0.y = Math.floor(this->y);
 return arg0;
 }

 Vector2f ceil() {
 this->x = Math.ceil(this->x);
 this->y = Math.ceil(this->y);
 return this;
 }

 Vector2f ceil(Vector2f arg0) {
 arg0.x = Math.ceil(this->x);
 arg0.y = Math.ceil(this->y);
 return arg0;
 }

 Vector2f round() {
 this->x = Math.ceil(this->x);
 this->y = Math.ceil(this->y);
 return this;
 }

 Vector2f round(Vector2f arg0) {
 arg0.x = Math.round(this->x);
 arg0.y = Math.round(this->y);
 return arg0;
 }

 bool isFinite() { return Math.isFinite(this->x) && Math.isFinite(this->y); }

 Vector2f absolute() {
 this->x = Math.abs(this->x);
 this->y = Math.abs(this->y);
 return this;
 }

 Vector2f absolute(Vector2f arg0) {
 arg0.x = Math.abs(this->x);
 arg0.y = Math.abs(this->y);
 return arg0;
 }
}
} // namespace joml
} // namespace org
