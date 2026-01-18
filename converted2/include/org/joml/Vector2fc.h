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

class Vector2fc {
public:
  virtual ~Vector2fc() = default;
  float x();

  float y();

  ByteBuffer get(ByteBuffer arg0);

  ByteBuffer get(int arg0, ByteBuffer arg1);

  FloatBuffer get(FloatBuffer arg0);

  FloatBuffer get(int arg0, FloatBuffer arg1);

  Vector2fc getToAddress(long arg0);

  Vector2f sub(Vector2fc arg0, Vector2f arg1);

  Vector2f sub(float arg0, float arg1, Vector2f arg2);

  float dot(Vector2fc arg0);

  float angle(Vector2fc arg0);

  float lengthSquared();

  float length();

  float distance(Vector2fc arg0);

  float distanceSquared(Vector2fc arg0);

  float distance(float arg0, float arg1);

  float distanceSquared(float arg0, float arg1);

  Vector2f normalize(Vector2f arg0);

  Vector2f normalize(float arg0, Vector2f arg1);

  Vector2f add(Vector2fc arg0, Vector2f arg1);

  Vector2f add(float arg0, float arg1, Vector2f arg2);

  Vector2f negate(Vector2f arg0);

  Vector2f mul(float arg0, Vector2f arg1);

  Vector2f mul(float arg0, float arg1, Vector2f arg2);

  Vector2f mul(Vector2fc arg0, Vector2f arg1);

  Vector2f div(float arg0, Vector2f arg1);

  Vector2f div(Vector2fc arg0, Vector2f arg1);

  Vector2f div(float arg0, float arg1, Vector2f arg2);

  Vector2f mul(Matrix2fc arg0, Vector2f arg1);

  Vector2f mul(Matrix2dc arg0, Vector2f arg1);

  Vector2f mulTranspose(Matrix2fc arg0, Vector2f arg1);

  Vector2f mulPosition(Matrix3x2fc arg0, Vector2f arg1);

  Vector2f mulDirection(Matrix3x2fc arg0, Vector2f arg1);

  Vector2f lerp(Vector2fc arg0, float arg1, Vector2f arg2);

  Vector2f fma(Vector2fc arg0, Vector2fc arg1, Vector2f arg2);

  Vector2f fma(float arg0, Vector2fc arg1, Vector2f arg2);

  Vector2f min(Vector2fc arg0, Vector2f arg1);

  Vector2f max(Vector2fc arg0, Vector2f arg1);

  int maxComponent();

  int minComponent();

  float get(int arg0);

  Vector2i get(int arg0, Vector2i arg1);

  Vector2f get(Vector2f arg0);

  Vector2d get(Vector2d arg0);

  Vector2f floor(Vector2f arg0);

  Vector2f ceil(Vector2f arg0);

  Vector2f round(Vector2f arg0);

  bool isFinite();

  Vector2f absolute(Vector2f arg0);

  bool equals(Vector2fc arg0, float arg1);

  bool equals(float arg0, float arg1);
}
} // namespace joml
} // namespace org
