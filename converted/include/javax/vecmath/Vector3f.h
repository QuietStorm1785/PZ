#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Vector3f : public Tuple3f {
public:
  static const long serialVersionUID = -7031930069184524614L;

public
  Vector3f(float float0, float float1, float float2) {
    super(float0, float1, float2);
  }

public
  Vector3f(float[] floats) { super(floats); }

public
  Vector3f(Vector3f vector3f1) { super(vector3f1); }

public
  Vector3f(Vector3d vector3d) { super(vector3d); }

public
  Vector3f(Tuple3f tuple3f) { super(tuple3f); }

public
  Vector3f(Tuple3d tuple3d) { super(tuple3d); }

public
  Vector3f() {}

  float lengthSquared() {
    return this.x * this.x + this.y * this.y + this.z * this.z;
  }

  float length() {
    return (float)Math.sqrt(this.x * this.x + this.y * this.y +
                            this.z * this.z);
  }

  void cross(Vector3f vector3f1, Vector3f vector3f0) {
    float float0 = vector3f1.y * vector3f0.z - vector3f1.z * vector3f0.y;
    float float1 = vector3f0.x * vector3f1.z - vector3f0.z * vector3f1.x;
    this.z = vector3f1.x * vector3f0.y - vector3f1.y * vector3f0.x;
    this.x = float0;
    this.y = float1;
  }

  float dot(Vector3f vector3f0) {
    return this.x * vector3f0.x + this.y * vector3f0.y + this.z * vector3f0.z;
  }

  void normalize(Vector3f vector3f0) {
    float float0 = (float)(1.0 / Math.sqrt(vector3f0.x * vector3f0.x +
                                           vector3f0.y * vector3f0.y +
                                           vector3f0.z * vector3f0.z));
    this.x = vector3f0.x * float0;
    this.y = vector3f0.y * float0;
    this.z = vector3f0.z * float0;
  }

  void normalize() {
    float float0 = (float)(1.0 / Math.sqrt(this.x * this.x + this.y * this.y +
                                           this.z * this.z));
    this.x *= float0;
    this.y *= float0;
    this.z *= float0;
  }

  float angle(Vector3f vector3f0) {
    double double0 = this.dot(vector3f0) / (this.length() * vector3f0.length());
    if (double0 < -1.0) {
      double0 = -1.0;
    }

    if (double0 > 1.0) {
      double0 = 1.0;
    }

    return (float)Math.acos(double0);
  }
}
} // namespace vecmath
} // namespace javax
