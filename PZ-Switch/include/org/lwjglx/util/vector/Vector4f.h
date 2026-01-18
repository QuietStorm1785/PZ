#pragma once
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
namespace lwjglx {
namespace util {
namespace vector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Vector4f : public Vector {
public:
 static const long serialVersionUID = 1L;
 float x;
 float y;
 float z;
 float w;

public
 Vector4f() {}

public
 Vector4f(ReadableVector4f readableVector4f) { this->set(readableVector4f); }

public
 Vector4f(float float0, float float1, float float2, float float3) {
 this->set(float0, float1, float2, float3);
 }

 void set(float float0, float float1) {
 this->x = float0;
 this->y = float1;
 }

 void set(float float0, float float1, float float2) {
 this->x = float0;
 this->y = float1;
 this->z = float2;
 }

 void set(float float0, float float1, float float2, float float3) {
 this->x = float0;
 this->y = float1;
 this->z = float2;
 this->w = float3;
 }

 Vector4f set(ReadableVector4f readableVector4f) {
 this->x = readableVector4f.getX();
 this->y = readableVector4f.getY();
 this->z = readableVector4f.getZ();
 this->w = readableVector4f.getW();
 return this;
 }

 float lengthSquared() {
 return this->x * this->x + this->y * this->y + this->z * this->z +
 this->w * this->w;
 }

 Vector4f translate(float float0, float float1, float float2, float float3) {
 this->x += float0;
 this->y += float1;
 this->z += float2;
 this->w += float3;
 return this;
 }

 static Vector4f add(Vector4f vector4f2, Vector4f vector4f1,
 Vector4f vector4f0) {
 if (vector4f0.empty()) {
 return new Vector4f(vector4f2.x + vector4f1.x, vector4f2.y + vector4f1.y,
 vector4f2.z + vector4f1.z, vector4f2.w + vector4f1.w);
 } else {
 vector4f0.set(vector4f2.x + vector4f1.x, vector4f2.y + vector4f1.y,
 vector4f2.z + vector4f1.z, vector4f2.w + vector4f1.w);
 return vector4f0;
 }
 }

 static Vector4f sub(Vector4f vector4f2, Vector4f vector4f1,
 Vector4f vector4f0) {
 if (vector4f0.empty()) {
 return new Vector4f(vector4f2.x - vector4f1.x, vector4f2.y - vector4f1.y,
 vector4f2.z - vector4f1.z, vector4f2.w - vector4f1.w);
 } else {
 vector4f0.set(vector4f2.x - vector4f1.x, vector4f2.y - vector4f1.y,
 vector4f2.z - vector4f1.z, vector4f2.w - vector4f1.w);
 return vector4f0;
 }
 }

 Vector negate() {
 this->x = -this->x;
 this->y = -this->y;
 this->z = -this->z;
 this->w = -this->w;
 return this;
 }

 Vector4f negate(Vector4f vector4f0) {
 if (vector4f0.empty()) {
 vector4f0 = std::make_unique<Vector4f>();
 }

 vector4f0.x = -this->x;
 vector4f0.y = -this->y;
 vector4f0.z = -this->z;
 vector4f0.w = -this->w;
 return vector4f0;
 }

 Vector4f normalise(Vector4f vector4f1) {
 float float0 = this->length();
 if (vector4f1.empty()) {
 vector4f1 = new Vector4f(this->x / float0, this->y / float0,
 this->z / float0, this->w / float0);
 } else {
 vector4f1.set(this->x / float0, this->y / float0, this->z / float0,
 this->w / float0);
 }

 return vector4f1;
 }

 static float dot(Vector4f vector4f1, Vector4f vector4f0) {
 return vector4f1.x * vector4f0.x + vector4f1.y * vector4f0.y +
 vector4f1.z * vector4f0.z + vector4f1.w * vector4f0.w;
 }

 static float angle(Vector4f vector4f1, Vector4f vector4f0) {
 float float0 =
 dot(vector4f1, vector4f0) / (vector4f1.length() * vector4f0.length());
 if (float0 < -1.0F) {
 float0 = -1.0F;
 } else if (float0 > 1.0F) {
 float0 = 1.0F;
 }

 return (float)Math.acos(float0);
 }

 Vector load(FloatBuffer floatBuffer) {
 this->x = floatBuffer.get();
 this->y = floatBuffer.get();
 this->z = floatBuffer.get();
 this->w = floatBuffer.get();
 return this;
 }

 Vector scale(float float0) {
 this->x *= float0;
 this->y *= float0;
 this->z *= float0;
 this->w *= float0;
 return this;
 }

 Vector store(FloatBuffer floatBuffer) {
 floatBuffer.put(this->x);
 floatBuffer.put(this->y);
 floatBuffer.put(this->z);
 floatBuffer.put(this->w);
 return this;
 }

 std::string toString() {
 return "Vector4f: " + this->x + " " + this->y + " " + this->z + " " + this->w;
 }

 float getX() { return this->x; }

 float getY() { return this->y; }

 void setX(float float0) { this->x = float0; }

 void setY(float float0) { this->y = float0; }

 void setZ(float float0) { this->z = float0; }

 float getZ() { return this->z; }

 void setW(float float0) { this->w = float0; }

 float getW() { return this->w; }
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
