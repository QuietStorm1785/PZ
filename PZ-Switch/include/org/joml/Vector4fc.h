#pragma once
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Vector4fc {
public:
 virtual ~Vector4fc() = default;
 float x();

 float y();

 float z();

 float w();

 FloatBuffer get(FloatBuffer arg0);

 FloatBuffer get(int arg0, FloatBuffer arg1);

 ByteBuffer get(ByteBuffer arg0);

 ByteBuffer get(int arg0, ByteBuffer arg1);

 Vector4fc getToAddress(long arg0);

 Vector4f sub(Vector4fc arg0, Vector4f arg1);

 Vector4f sub(float arg0, float arg1, float arg2, float arg3, Vector4f arg4);

 Vector4f add(Vector4fc arg0, Vector4f arg1);

 Vector4f add(float arg0, float arg1, float arg2, float arg3, Vector4f arg4);

 Vector4f fma(Vector4fc arg0, Vector4fc arg1, Vector4f arg2);

 Vector4f fma(float arg0, Vector4fc arg1, Vector4f arg2);

 Vector4f mulAdd(Vector4fc arg0, Vector4fc arg1, Vector4f arg2);

 Vector4f mulAdd(float arg0, Vector4fc arg1, Vector4f arg2);

 Vector4f mul(Vector4fc arg0, Vector4f arg1);

 Vector4f div(Vector4fc arg0, Vector4f arg1);

 Vector4f mul(Matrix4fc arg0, Vector4f arg1);

 Vector4f mulTranspose(Matrix4fc arg0, Vector4f arg1);

 Vector4f mulAffine(Matrix4fc arg0, Vector4f arg1);

 Vector4f mulAffineTranspose(Matrix4fc arg0, Vector4f arg1);

 Vector4f mul(Matrix4x3fc arg0, Vector4f arg1);

 Vector4f mulProject(Matrix4fc arg0, Vector4f arg1);

 Vector3f mulProject(Matrix4fc arg0, Vector3f arg1);

 Vector4f mul(float arg0, Vector4f arg1);

 Vector4f mul(float arg0, float arg1, float arg2, float arg3, Vector4f arg4);

 Vector4f div(float arg0, Vector4f arg1);

 Vector4f div(float arg0, float arg1, float arg2, float arg3, Vector4f arg4);

 Vector4f rotate(Quaternionfc arg0, Vector4f arg1);

 Vector4f rotateAxis(float arg0, float arg1, float arg2, float arg3,
 Vector4f arg4);

 Vector4f rotateX(float arg0, Vector4f arg1);

 Vector4f rotateY(float arg0, Vector4f arg1);

 Vector4f rotateZ(float arg0, Vector4f arg1);

 float lengthSquared();

 float length();

 Vector4f normalize(Vector4f arg0);

 Vector4f normalize(float arg0, Vector4f arg1);

 Vector4f normalize3(Vector4f arg0);

 float distance(Vector4fc arg0);

 float distance(float arg0, float arg1, float arg2, float arg3);

 float distanceSquared(Vector4fc arg0);

 float distanceSquared(float arg0, float arg1, float arg2, float arg3);

 float dot(Vector4fc arg0);

 float dot(float arg0, float arg1, float arg2, float arg3);

 float angleCos(Vector4fc arg0);

 float angle(Vector4fc arg0);

 Vector4f negate(Vector4f arg0);

 Vector4f min(Vector4fc arg0, Vector4f arg1);

 Vector4f max(Vector4fc arg0, Vector4f arg1);

 Vector4f lerp(Vector4fc arg0, float arg1, Vector4f arg2);

 Vector4f smoothStep(Vector4fc arg0, float arg1, Vector4f arg2);

 Vector4f hermite(Vector4fc arg0, Vector4fc arg1, Vector4fc arg2, float arg3,
 Vector4f arg4);

 float get(int arg0);

 Vector4i get(int arg0, Vector4i arg1);

 Vector4f get(Vector4f arg0);

 Vector4d get(Vector4d arg0);

 int maxComponent();

 int minComponent();

 Vector4f floor(Vector4f arg0);

 Vector4f ceil(Vector4f arg0);

 Vector4f round(Vector4f arg0);

 bool isFinite();

 Vector4f absolute(Vector4f arg0);

 bool equals(Vector4fc arg0, float arg1);

 bool equals(float arg0, float arg1, float arg2, float arg3);
}
} // namespace joml
} // namespace org
