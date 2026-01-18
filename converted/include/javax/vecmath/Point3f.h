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

class Point3f : public Tuple3f {
public:
  static const long serialVersionUID = -8689337816398030143L;

public
  Point3f(float float0, float float1, float float2) {
    super(float0, float1, float2);
  }

public
  Point3f(float[] floats) { super(floats); }

public
  Point3f(Point3f point3f1) { super(point3f1); }

public
  Point3f(Point3d point3d) { super(point3d); }

public
  Point3f(Tuple3f tuple3f) { super(tuple3f); }

public
  Point3f(Tuple3d tuple3d) { super(tuple3d); }

public
  Point3f() {}

  float distanceSquared(Point3f point3f0) {
    float float0 = this.x - point3f0.x;
    float float1 = this.y - point3f0.y;
    float float2 = this.z - point3f0.z;
    return float0 * float0 + float1 * float1 + float2 * float2;
  }

  float distance(Point3f point3f0) {
    float float0 = this.x - point3f0.x;
    float float1 = this.y - point3f0.y;
    float float2 = this.z - point3f0.z;
    return (float)Math.sqrt(float0 * float0 + float1 * float1 +
                            float2 * float2);
  }

  float distanceL1(Point3f point3f0) {
    return Math.abs(this.x - point3f0.x) + Math.abs(this.y - point3f0.y) +
           Math.abs(this.z - point3f0.z);
  }

  float distanceLinf(Point3f point3f0) {
    float float0 =
        Math.max(Math.abs(this.x - point3f0.x), Math.abs(this.y - point3f0.y));
    return Math.max(float0, Math.abs(this.z - point3f0.z));
  }

  void project(Point4f point4f) {
    float float0 = 1.0F / point4f.w;
    this.x = point4f.x * float0;
    this.y = point4f.y * float0;
    this.z = point4f.z * float0;
  }
}
} // namespace vecmath
} // namespace javax
