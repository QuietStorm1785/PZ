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

class Vector2f : public Vector {
public:
  static const long serialVersionUID = 1L;
  float x;
  float y;

public
  Vector2f() {}

public
  Vector2f(ReadableVector2f readableVector2f) { this.set(readableVector2f); }

public
  Vector2f(float float0, float float1) { this.set(float0, float1); }

  void set(float float0, float float1) {
    this.x = float0;
    this.y = float1;
  }

  Vector2f set(ReadableVector2f readableVector2f) {
    this.x = readableVector2f.getX();
    this.y = readableVector2f.getY();
    return this;
  }

  float lengthSquared() { return this.x * this.x + this.y * this.y; }

  Vector2f translate(float float0, float float1) {
    this.x += float0;
    this.y += float1;
    return this;
  }

  Vector negate() {
    this.x = -this.x;
    this.y = -this.y;
    return this;
  }

  Vector2f negate(Vector2f vector2f0) {
    if (vector2f0 == nullptr) {
      vector2f0 = std::make_unique<Vector2f>();
    }

    vector2f0.x = -this.x;
    vector2f0.y = -this.y;
    return vector2f0;
  }

  Vector2f normalise(Vector2f vector2f1) {
    float float0 = this.length();
    if (vector2f1 == nullptr) {
      vector2f1 = new Vector2f(this.x / float0, this.y / float0);
    } else {
      vector2f1.set(this.x / float0, this.y / float0);
    }

    return vector2f1;
  }

  static float dot(Vector2f vector2f1, Vector2f vector2f0) {
    return vector2f1.x * vector2f0.x + vector2f1.y * vector2f0.y;
  }

  static float angle(Vector2f vector2f1, Vector2f vector2f0) {
    float float0 =
        dot(vector2f1, vector2f0) / (vector2f1.length() * vector2f0.length());
    if (float0 < -1.0F) {
      float0 = -1.0F;
    } else if (float0 > 1.0F) {
      float0 = 1.0F;
    }

    return (float)Math.acos(float0);
  }

  static Vector2f add(Vector2f vector2f2, Vector2f vector2f1,
                      Vector2f vector2f0) {
    if (vector2f0 == nullptr) {
      return new Vector2f(vector2f2.x + vector2f1.x, vector2f2.y + vector2f1.y);
    } else {
      vector2f0.set(vector2f2.x + vector2f1.x, vector2f2.y + vector2f1.y);
      return vector2f0;
    }
  }

  static Vector2f sub(Vector2f vector2f2, Vector2f vector2f1,
                      Vector2f vector2f0) {
    if (vector2f0 == nullptr) {
      return new Vector2f(vector2f2.x - vector2f1.x, vector2f2.y - vector2f1.y);
    } else {
      vector2f0.set(vector2f2.x - vector2f1.x, vector2f2.y - vector2f1.y);
      return vector2f0;
    }
  }

  Vector store(FloatBuffer floatBuffer) {
    floatBuffer.put(this.x);
    floatBuffer.put(this.y);
    return this;
  }

  Vector load(FloatBuffer floatBuffer) {
    this.x = floatBuffer.get();
    this.y = floatBuffer.get();
    return this;
  }

  Vector scale(float float0) {
    this.x *= float0;
    this.y *= float0;
    return this;
  }

  std::string toString() {
    StringBuilder stringBuilder = new StringBuilder(64);
    stringBuilder.append("Vector2f[");
    stringBuilder.append(this.x);
    stringBuilder.append(", ");
    stringBuilder.append(this.y);
    stringBuilder.append(']');
    return stringBuilder.toString();
  }

  float getX() { return this.x; }

  float getY() { return this.y; }

  void setX(float float0) { this.x = float0; }

  void setY(float float0) { this.y = float0; }
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
