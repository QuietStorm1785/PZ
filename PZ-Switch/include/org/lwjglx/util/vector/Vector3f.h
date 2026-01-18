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

class Vector3f : public Vector {
public:
 static const long serialVersionUID = 1L;
 float x;
 float y;
 float z;

public
 Vector3f() {}

public
 Vector3f(ReadableVector3f readableVector3f) { this->set(readableVector3f); }

public
 Vector3f(float float0, float float1, float float2) {
 this->set(float0, float1, float2);
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

 Vector3f set(ReadableVector3f readableVector3f) {
 this->x = readableVector3f.getX();
 this->y = readableVector3f.getY();
 this->z = readableVector3f.getZ();
 return this;
 }

 float lengthSquared() {
 return this->x * this->x + this->y * this->y + this->z * this->z;
 }

 Vector3f translate(float float0, float float1, float float2) {
 this->x += float0;
 this->y += float1;
 this->z += float2;
 return this;
 }

 static Vector3f add(Vector3f vector3f2, Vector3f vector3f1,
 Vector3f vector3f0) {
 if (vector3f0.empty()) {
 return new Vector3f(vector3f2.x + vector3f1.x, vector3f2.y + vector3f1.y,
 vector3f2.z + vector3f1.z);
 } else {
 vector3f0.set(vector3f2.x + vector3f1.x, vector3f2.y + vector3f1.y,
 vector3f2.z + vector3f1.z);
 return vector3f0;
 }
 }

 static Vector3f sub(Vector3f vector3f2, Vector3f vector3f1,
 Vector3f vector3f0) {
 if (vector3f0.empty()) {
 return new Vector3f(vector3f2.x - vector3f1.x, vector3f2.y - vector3f1.y,
 vector3f2.z - vector3f1.z);
 } else {
 vector3f0.set(vector3f2.x - vector3f1.x, vector3f2.y - vector3f1.y,
 vector3f2.z - vector3f1.z);
 return vector3f0;
 }
 }

 static Vector3f cross(Vector3f vector3f2, Vector3f vector3f1,
 Vector3f vector3f0) {
 if (vector3f0.empty()) {
 vector3f0 = std::make_unique<Vector3f>();
 }

 vector3f0.set(vector3f2.y * vector3f1.z - vector3f2.z * vector3f1.y,
 vector3f1.x * vector3f2.z - vector3f1.z * vector3f2.x,
 vector3f2.x * vector3f1.y - vector3f2.y * vector3f1.x);
 return vector3f0;
 }

 Vector negate() {
 this->x = -this->x;
 this->y = -this->y;
 this->z = -this->z;
 return this;
 }

 Vector3f negate(Vector3f vector3f0) {
 if (vector3f0.empty()) {
 vector3f0 = std::make_unique<Vector3f>();
 }

 vector3f0.x = -this->x;
 vector3f0.y = -this->y;
 vector3f0.z = -this->z;
 return vector3f0;
 }

 Vector3f normalise(Vector3f vector3f1) {
 float float0 = this->length();
 if (vector3f1.empty()) {
 vector3f1 =
 new Vector3f(this->x / float0, this->y / float0, this->z / float0);
 } else {
 vector3f1.set(this->x / float0, this->y / float0, this->z / float0);
 }

 return vector3f1;
 }

 static float dot(Vector3f vector3f1, Vector3f vector3f0) {
 return vector3f1.x * vector3f0.x + vector3f1.y * vector3f0.y +
 vector3f1.z * vector3f0.z;
 }

 static float angle(Vector3f vector3f1, Vector3f vector3f0) {
 float float0 =
 dot(vector3f1, vector3f0) / (vector3f1.length() * vector3f0.length());
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
 return this;
 }

 Vector scale(float float0) {
 this->x *= float0;
 this->y *= float0;
 this->z *= float0;
 return this;
 }

 Vector store(FloatBuffer floatBuffer) {
 floatBuffer.put(this->x);
 floatBuffer.put(this->y);
 floatBuffer.put(this->z);
 return this;
 }

 std::string toString() {
 StringBuilder stringBuilder = new StringBuilder(64);
 stringBuilder.append("Vector3f[");
 stringBuilder.append(this->x);
 stringBuilder.append(", ");
 stringBuilder.append(this->y);
 stringBuilder.append(", ");
 stringBuilder.append(this->z);
 stringBuilder.append(']');
 return stringBuilder.toString();
 }

 float getX() { return this->x; }

 float getY() { return this->y; }

 void setX(float float0) { this->x = float0; }

 void setY(float float0) { this->y = float0; }

 void setZ(float float0) { this->z = float0; }

 float getZ() { return this->z; }
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
