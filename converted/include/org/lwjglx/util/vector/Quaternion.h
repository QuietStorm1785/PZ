#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace org {
namespace lwjglx {
namespace util {
namespace vector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Quaternion : public Vector {
public:
 static const long serialVersionUID = 1L;
 float x;
 float y;
 float z;
 float w;

 public Quaternion() {
 this->setIdentity();
 }

 public Quaternion(ReadableVector4f readableVector4f) {
 this->set(readableVector4f);
 }

 public Quaternion(float float0, float float1, float float2, float float3) {
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

 Quaternion set(ReadableVector4f readableVector4f) {
 this->x = readableVector4f.getX();
 this->y = readableVector4f.getY();
 this->z = readableVector4f.getZ();
 this->w = readableVector4f.getW();
 return this;
 }

 Quaternion setIdentity() {
 return setIdentity();
 }

 static Quaternion setIdentity(Quaternion quaternion) {
 quaternion.x = 0.0F;
 quaternion.y = 0.0F;
 quaternion.z = 0.0F;
 quaternion.w = 1.0F;
 return quaternion;
 }

 float lengthSquared() {
 return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
 }

 static Quaternion normalise(Quaternion quaternion0, Quaternion quaternion1) {
 float float0 = 1.0F / quaternion0.length();
 if (quaternion1 == nullptr) {
 quaternion1 = std::make_unique<Quaternion>();
 }

 quaternion1.set(quaternion0.x * float0, quaternion0.y * float0, quaternion0.z * float0, quaternion0.w * float0);
 return quaternion1;
 }

 Quaternion normalise(Quaternion quaternion1) {
 return normalise();
 }

 static float dot(Quaternion quaternion1, Quaternion quaternion0) {
 return quaternion1.x * quaternion0.x + quaternion1.y * quaternion0.y + quaternion1.z * quaternion0.z + quaternion1.w * quaternion0.w;
 }

 Quaternion negate(Quaternion quaternion1) {
 return negate();
 }

 static Quaternion negate(Quaternion quaternion1, Quaternion quaternion0) {
 if (quaternion0 == nullptr) {
 quaternion0 = std::make_unique<Quaternion>();
 }

 quaternion0.x = -quaternion1.x;
 quaternion0.y = -quaternion1.y;
 quaternion0.z = -quaternion1.z;
 quaternion0.w = quaternion1.w;
 return quaternion0;
 }

 Vector negate() {
 return negate();
 }

 Vector load(FloatBuffer floatBuffer) {
 this->x = floatBuffer.get();
 this->y = floatBuffer.get();
 this->z = floatBuffer.get();
 this->w = floatBuffer.get();
 return this;
 }

 Vector scale(float float0) {
 return scale();
 }

 static Quaternion scale(float float0, Quaternion quaternion1, Quaternion quaternion0) {
 if (quaternion0 == nullptr) {
 quaternion0 = std::make_unique<Quaternion>();
 }

 quaternion0.x = quaternion1.x * float0;
 quaternion0.y = quaternion1.y * float0;
 quaternion0.z = quaternion1.z * float0;
 quaternion0.w = quaternion1.w * float0;
 return quaternion0;
 }

 Vector store(FloatBuffer floatBuffer) {
 floatBuffer.put(this->x);
 floatBuffer.put(this->y);
 floatBuffer.put(this->z);
 floatBuffer.put(this->w);
 return this;
 }

 float getX() {
 return this->x;
 }

 float getY() {
 return this->y;
 }

 void setX(float float0) {
 this->x = float0;
 }

 void setY(float float0) {
 this->y = float0;
 }

 void setZ(float float0) {
 this->z = float0;
 }

 float getZ() {
 return this->z;
 }

 void setW(float float0) {
 this->w = float0;
 }

 float getW() {
 return this->w;
 }

 std::string toString() {
 return "Quaternion: " + this->x + " " + this->y + " " + this->z + " " + this->w;
 }

 static Quaternion mul(Quaternion quaternion2, Quaternion quaternion1, Quaternion quaternion0) {
 if (quaternion0 == nullptr) {
 quaternion0 = std::make_unique<Quaternion>();
 }

 quaternion0.set(
 quaternion2.x * quaternion1.w + quaternion2.w * quaternion1.x + quaternion2.y * quaternion1.z - quaternion2.z * quaternion1.y,
 quaternion2.y * quaternion1.w + quaternion2.w * quaternion1.y + quaternion2.z * quaternion1.x - quaternion2.x * quaternion1.z,
 quaternion2.z * quaternion1.w + quaternion2.w * quaternion1.z + quaternion2.x * quaternion1.y - quaternion2.y * quaternion1.x,
 quaternion2.w * quaternion1.w - quaternion2.x * quaternion1.x - quaternion2.y * quaternion1.y - quaternion2.z * quaternion1.z
 );
 return quaternion0;
 }

 static Quaternion mulInverse(Quaternion quaternion2, Quaternion quaternion0, Quaternion quaternion1) {
 float float0 = quaternion0.lengthSquared();
 float0 = float0 == 0.0 ? float0 : 1.0F / float0;
 if (quaternion1 == nullptr) {
 quaternion1 = std::make_unique<Quaternion>();
 }

 quaternion1.set(
 (quaternion2.x * quaternion0.w - quaternion2.w * quaternion0.x - quaternion2.y * quaternion0.z + quaternion2.z * quaternion0.y) * float0,
 (quaternion2.y * quaternion0.w - quaternion2.w * quaternion0.y - quaternion2.z * quaternion0.x + quaternion2.x * quaternion0.z) * float0,
 (quaternion2.z * quaternion0.w - quaternion2.w * quaternion0.z - quaternion2.x * quaternion0.y + quaternion2.y * quaternion0.x) * float0,
 (quaternion2.w * quaternion0.w + quaternion2.x * quaternion0.x + quaternion2.y * quaternion0.y + quaternion2.z * quaternion0.z) * float0
 );
 return quaternion1;
 }

 void setFromAxisAngle(Vector4f vector4f) {
 this->x = vector4f.x;
 this->y = vector4f.y;
 this->z = vector4f.z;
 float float0 = (float)Math.sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
 float float1 = (float)(Math.sin(0.5 * vector4f.w) / float0);
 this->x *= float1;
 this->y *= float1;
 this->z *= float1;
 this->w = (float)Math.cos(0.5 * vector4f.w);
 }

 Quaternion setFromMatrix(Matrix4f matrix4f) {
 return setFromMatrix();
 }

 static Quaternion setFromMatrix(Matrix4f matrix4f, Quaternion quaternion) {
 return quaternion.setFromMat(
 matrix4f.m00, matrix4f.m01, matrix4f.m02, matrix4f.m10, matrix4f.m11, matrix4f.m12, matrix4f.m20, matrix4f.m21, matrix4f.m22
 );
 }

 Quaternion setFromMatrix(Matrix3f matrix3f) {
 return setFromMatrix();
 }

 static Quaternion setFromMatrix(Matrix3f matrix3f, Quaternion quaternion) {
 return quaternion.setFromMat(
 matrix3f.m00, matrix3f.m01, matrix3f.m02, matrix3f.m10, matrix3f.m11, matrix3f.m12, matrix3f.m20, matrix3f.m21, matrix3f.m22
 );
 }

 Quaternion setFromMat(float float2, float float10, float float7, float float9, float float3, float float6, float float8, float float5, float float1) {
 float float0 = float2 + float3 + float1;
 if (float0 >= 0.0) {
 float float4 = (float)Math.sqrt(float0 + 1.0);
 this->w = float4 * 0.5F;
 float4 = 0.5F / float4;
 this->x = (float5 - float6) * float4;
 this->y = (float7 - float8) * float4;
 this->z = (float9 - float10) * float4;
 } else {
 float float11 = Math.max(Math.max(float2, float3), float1);
 if (float11 == float2) {
 float float12 = (float)Math.sqrt(float2 - (float3 + float1) + 1.0);
 this->x = float12 * 0.5F;
 float12 = 0.5F / float12;
 this->y = (float10 + float9) * float12;
 this->z = (float8 + float7) * float12;
 this->w = (float5 - float6) * float12;
 } else if (float11 == float3) {
 float float13 = (float)Math.sqrt(float3 - (float1 + float2) + 1.0);
 this->y = float13 * 0.5F;
 float13 = 0.5F / float13;
 this->z = (float6 + float5) * float13;
 this->x = (float10 + float9) * float13;
 this->w = (float7 - float8) * float13;
 } else {
 float float14 = (float)Math.sqrt(float1 - (float2 + float3) + 1.0);
 this->z = float14 * 0.5F;
 float14 = 0.5F / float14;
 this->x = (float8 + float7) * float14;
 this->y = (float6 + float5) * float14;
 this->w = (float9 - float10) * float14;
 }
 }

 return this;
 }
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
