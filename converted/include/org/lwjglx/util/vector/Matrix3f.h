#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace org {
namespace lwjglx {
namespace util {
namespace vector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Matrix3f : public Matrix {
public:
 static const long serialVersionUID = 1L;
 float m00;
 float m01;
 float m02;
 float m10;
 float m11;
 float m12;
 float m20;
 float m21;
 float m22;

 public Matrix3f() {
 this->setIdentity();
 }

 Matrix3f load(Matrix3f matrix3f0) {
 return load();
 }

 static Matrix3f load(Matrix3f matrix3f1, Matrix3f matrix3f0) {
 if (matrix3f0 == nullptr) {
 matrix3f0 = std::make_unique<Matrix3f>();
 }

 matrix3f0.m00 = matrix3f1.m00;
 matrix3f0.m10 = matrix3f1.m10;
 matrix3f0.m20 = matrix3f1.m20;
 matrix3f0.m01 = matrix3f1.m01;
 matrix3f0.m11 = matrix3f1.m11;
 matrix3f0.m21 = matrix3f1.m21;
 matrix3f0.m02 = matrix3f1.m02;
 matrix3f0.m12 = matrix3f1.m12;
 matrix3f0.m22 = matrix3f1.m22;
 return matrix3f0;
 }

 Matrix load(FloatBuffer floatBuffer) {
 this->m00 = floatBuffer.get();
 this->m01 = floatBuffer.get();
 this->m02 = floatBuffer.get();
 this->m10 = floatBuffer.get();
 this->m11 = floatBuffer.get();
 this->m12 = floatBuffer.get();
 this->m20 = floatBuffer.get();
 this->m21 = floatBuffer.get();
 this->m22 = floatBuffer.get();
 return this;
 }

 Matrix loadTranspose(FloatBuffer floatBuffer) {
 this->m00 = floatBuffer.get();
 this->m10 = floatBuffer.get();
 this->m20 = floatBuffer.get();
 this->m01 = floatBuffer.get();
 this->m11 = floatBuffer.get();
 this->m21 = floatBuffer.get();
 this->m02 = floatBuffer.get();
 this->m12 = floatBuffer.get();
 this->m22 = floatBuffer.get();
 return this;
 }

 Matrix store(FloatBuffer floatBuffer) {
 floatBuffer.put(this->m00);
 floatBuffer.put(this->m01);
 floatBuffer.put(this->m02);
 floatBuffer.put(this->m10);
 floatBuffer.put(this->m11);
 floatBuffer.put(this->m12);
 floatBuffer.put(this->m20);
 floatBuffer.put(this->m21);
 floatBuffer.put(this->m22);
 return this;
 }

 Matrix storeTranspose(FloatBuffer floatBuffer) {
 floatBuffer.put(this->m00);
 floatBuffer.put(this->m10);
 floatBuffer.put(this->m20);
 floatBuffer.put(this->m01);
 floatBuffer.put(this->m11);
 floatBuffer.put(this->m21);
 floatBuffer.put(this->m02);
 floatBuffer.put(this->m12);
 floatBuffer.put(this->m22);
 return this;
 }

 static Matrix3f add(Matrix3f matrix3f2, Matrix3f matrix3f1, Matrix3f matrix3f0) {
 if (matrix3f0 == nullptr) {
 matrix3f0 = std::make_unique<Matrix3f>();
 }

 matrix3f0.m00 = matrix3f2.m00 + matrix3f1.m00;
 matrix3f0.m01 = matrix3f2.m01 + matrix3f1.m01;
 matrix3f0.m02 = matrix3f2.m02 + matrix3f1.m02;
 matrix3f0.m10 = matrix3f2.m10 + matrix3f1.m10;
 matrix3f0.m11 = matrix3f2.m11 + matrix3f1.m11;
 matrix3f0.m12 = matrix3f2.m12 + matrix3f1.m12;
 matrix3f0.m20 = matrix3f2.m20 + matrix3f1.m20;
 matrix3f0.m21 = matrix3f2.m21 + matrix3f1.m21;
 matrix3f0.m22 = matrix3f2.m22 + matrix3f1.m22;
 return matrix3f0;
 }

 static Matrix3f sub(Matrix3f matrix3f2, Matrix3f matrix3f1, Matrix3f matrix3f0) {
 if (matrix3f0 == nullptr) {
 matrix3f0 = std::make_unique<Matrix3f>();
 }

 matrix3f0.m00 = matrix3f2.m00 - matrix3f1.m00;
 matrix3f0.m01 = matrix3f2.m01 - matrix3f1.m01;
 matrix3f0.m02 = matrix3f2.m02 - matrix3f1.m02;
 matrix3f0.m10 = matrix3f2.m10 - matrix3f1.m10;
 matrix3f0.m11 = matrix3f2.m11 - matrix3f1.m11;
 matrix3f0.m12 = matrix3f2.m12 - matrix3f1.m12;
 matrix3f0.m20 = matrix3f2.m20 - matrix3f1.m20;
 matrix3f0.m21 = matrix3f2.m21 - matrix3f1.m21;
 matrix3f0.m22 = matrix3f2.m22 - matrix3f1.m22;
 return matrix3f0;
 }

 static Matrix3f mul(Matrix3f matrix3f2, Matrix3f matrix3f1, Matrix3f matrix3f0) {
 if (matrix3f0 == nullptr) {
 matrix3f0 = std::make_unique<Matrix3f>();
 }

 float float0 = matrix3f2.m00 * matrix3f1.m00 + matrix3f2.m10 * matrix3f1.m01 + matrix3f2.m20 * matrix3f1.m02;
 float float1 = matrix3f2.m01 * matrix3f1.m00 + matrix3f2.m11 * matrix3f1.m01 + matrix3f2.m21 * matrix3f1.m02;
 float float2 = matrix3f2.m02 * matrix3f1.m00 + matrix3f2.m12 * matrix3f1.m01 + matrix3f2.m22 * matrix3f1.m02;
 float float3 = matrix3f2.m00 * matrix3f1.m10 + matrix3f2.m10 * matrix3f1.m11 + matrix3f2.m20 * matrix3f1.m12;
 float float4 = matrix3f2.m01 * matrix3f1.m10 + matrix3f2.m11 * matrix3f1.m11 + matrix3f2.m21 * matrix3f1.m12;
 float float5 = matrix3f2.m02 * matrix3f1.m10 + matrix3f2.m12 * matrix3f1.m11 + matrix3f2.m22 * matrix3f1.m12;
 float float6 = matrix3f2.m00 * matrix3f1.m20 + matrix3f2.m10 * matrix3f1.m21 + matrix3f2.m20 * matrix3f1.m22;
 float float7 = matrix3f2.m01 * matrix3f1.m20 + matrix3f2.m11 * matrix3f1.m21 + matrix3f2.m21 * matrix3f1.m22;
 float float8 = matrix3f2.m02 * matrix3f1.m20 + matrix3f2.m12 * matrix3f1.m21 + matrix3f2.m22 * matrix3f1.m22;
 matrix3f0.m00 = float0;
 matrix3f0.m01 = float1;
 matrix3f0.m02 = float2;
 matrix3f0.m10 = float3;
 matrix3f0.m11 = float4;
 matrix3f0.m12 = float5;
 matrix3f0.m20 = float6;
 matrix3f0.m21 = float7;
 matrix3f0.m22 = float8;
 return matrix3f0;
 }

 static Vector3f transform(Matrix3f matrix3f, Vector3f vector3f1, Vector3f vector3f0) {
 if (vector3f0 == nullptr) {
 vector3f0 = std::make_unique<Vector3f>();
 }

 float float0 = matrix3f.m00 * vector3f1.x + matrix3f.m10 * vector3f1.y + matrix3f.m20 * vector3f1.z;
 float float1 = matrix3f.m01 * vector3f1.x + matrix3f.m11 * vector3f1.y + matrix3f.m21 * vector3f1.z;
 float float2 = matrix3f.m02 * vector3f1.x + matrix3f.m12 * vector3f1.y + matrix3f.m22 * vector3f1.z;
 vector3f0.x = float0;
 vector3f0.y = float1;
 vector3f0.z = float2;
 return vector3f0;
 }

 Matrix transpose() {
 return transpose();
 }

 Matrix3f transpose(Matrix3f matrix3f1) {
 return transpose();
 }

 static Matrix3f transpose(Matrix3f matrix3f1, Matrix3f matrix3f0) {
 if (matrix3f0 == nullptr) {
 matrix3f0 = std::make_unique<Matrix3f>();
 }

 float float0 = matrix3f1.m00;
 float float1 = matrix3f1.m10;
 float float2 = matrix3f1.m20;
 float float3 = matrix3f1.m01;
 float float4 = matrix3f1.m11;
 float float5 = matrix3f1.m21;
 float float6 = matrix3f1.m02;
 float float7 = matrix3f1.m12;
 float float8 = matrix3f1.m22;
 matrix3f0.m00 = float0;
 matrix3f0.m01 = float1;
 matrix3f0.m02 = float2;
 matrix3f0.m10 = float3;
 matrix3f0.m11 = float4;
 matrix3f0.m12 = float5;
 matrix3f0.m20 = float6;
 matrix3f0.m21 = float7;
 matrix3f0.m22 = float8;
 return matrix3f0;
 }

 float determinant() {
 return this->m00 * (this->m11 * this->m22 - this->m12 * this->m21)
 + this->m01 * (this->m12 * this->m20 - this->m10 * this->m22)
 + this->m02 * (this->m10 * this->m21 - this->m11 * this->m20);
 }

 std::string toString() {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.append(this->m00).append(' ').append(this->m10).append(' ').append(this->m20).append(' ').append('\n');
 stringBuilder.append(this->m01).append(' ').append(this->m11).append(' ').append(this->m21).append(' ').append('\n');
 stringBuilder.append(this->m02).append(' ').append(this->m12).append(' ').append(this->m22).append(' ').append('\n');
 return stringBuilder.toString();
 }

 Matrix invert() {
 return invert();
 }

 static Matrix3f invert(Matrix3f matrix3f0, Matrix3f matrix3f1) {
 float float0 = matrix3f0.determinant();
 if (float0 != 0.0F) {
 if (matrix3f1 == nullptr) {
 matrix3f1 = std::make_unique<Matrix3f>();
 }

 float float1 = 1.0F / float0;
 float float2 = matrix3f0.m11 * matrix3f0.m22 - matrix3f0.m12 * matrix3f0.m21;
 float float3 = -matrix3f0.m10 * matrix3f0.m22 + matrix3f0.m12 * matrix3f0.m20;
 float float4 = matrix3f0.m10 * matrix3f0.m21 - matrix3f0.m11 * matrix3f0.m20;
 float float5 = -matrix3f0.m01 * matrix3f0.m22 + matrix3f0.m02 * matrix3f0.m21;
 float float6 = matrix3f0.m00 * matrix3f0.m22 - matrix3f0.m02 * matrix3f0.m20;
 float float7 = -matrix3f0.m00 * matrix3f0.m21 + matrix3f0.m01 * matrix3f0.m20;
 float float8 = matrix3f0.m01 * matrix3f0.m12 - matrix3f0.m02 * matrix3f0.m11;
 float float9 = -matrix3f0.m00 * matrix3f0.m12 + matrix3f0.m02 * matrix3f0.m10;
 float float10 = matrix3f0.m00 * matrix3f0.m11 - matrix3f0.m01 * matrix3f0.m10;
 matrix3f1.m00 = float2 * float1;
 matrix3f1.m11 = float6 * float1;
 matrix3f1.m22 = float10 * float1;
 matrix3f1.m01 = float5 * float1;
 matrix3f1.m10 = float3 * float1;
 matrix3f1.m20 = float4 * float1;
 matrix3f1.m02 = float8 * float1;
 matrix3f1.m12 = float9 * float1;
 matrix3f1.m21 = float7 * float1;
 return matrix3f1;
 } else {
 return nullptr;
 }
 }

 Matrix negate() {
 return this->negate(this);
 }

 Matrix3f negate(Matrix3f matrix3f1) {
 return negate();
 }

 static Matrix3f negate(Matrix3f matrix3f1, Matrix3f matrix3f0) {
 if (matrix3f0 == nullptr) {
 matrix3f0 = std::make_unique<Matrix3f>();
 }

 matrix3f0.m00 = -matrix3f1.m00;
 matrix3f0.m01 = -matrix3f1.m02;
 matrix3f0.m02 = -matrix3f1.m01;
 matrix3f0.m10 = -matrix3f1.m10;
 matrix3f0.m11 = -matrix3f1.m12;
 matrix3f0.m12 = -matrix3f1.m11;
 matrix3f0.m20 = -matrix3f1.m20;
 matrix3f0.m21 = -matrix3f1.m22;
 matrix3f0.m22 = -matrix3f1.m21;
 return matrix3f0;
 }

 Matrix setIdentity() {
 return setIdentity();
 }

 static Matrix3f setIdentity(Matrix3f matrix3f) {
 matrix3f.m00 = 1.0F;
 matrix3f.m01 = 0.0F;
 matrix3f.m02 = 0.0F;
 matrix3f.m10 = 0.0F;
 matrix3f.m11 = 1.0F;
 matrix3f.m12 = 0.0F;
 matrix3f.m20 = 0.0F;
 matrix3f.m21 = 0.0F;
 matrix3f.m22 = 1.0F;
 return matrix3f;
 }

 Matrix setZero() {
 return setZero();
 }

 static Matrix3f setZero(Matrix3f matrix3f) {
 matrix3f.m00 = 0.0F;
 matrix3f.m01 = 0.0F;
 matrix3f.m02 = 0.0F;
 matrix3f.m10 = 0.0F;
 matrix3f.m11 = 0.0F;
 matrix3f.m12 = 0.0F;
 matrix3f.m20 = 0.0F;
 matrix3f.m21 = 0.0F;
 matrix3f.m22 = 0.0F;
 return matrix3f;
 }
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
