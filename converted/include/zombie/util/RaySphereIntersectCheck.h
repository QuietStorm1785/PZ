#pragma once
#include "zombie/iso/Vector3.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RaySphereIntersectCheck {
public:
  static Vector3 toSphere = std::make_unique<Vector3>();
  static Vector3 dirNormal = std::make_unique<Vector3>();

  static bool intersects(Vector3 vector1, Vector3 vector0, Vector3 vector2,
                         float float0) {
    float0 *= float0;
    dirNormal.x = vector0.x;
    dirNormal.y = vector0.y;
    dirNormal.z = vector0.z;
    dirNormal.normalize();
    toSphere.x = vector2.x - vector1.x;
    toSphere.y = vector2.y - vector1.y;
    toSphere.z = vector2.z - vector1.z;
    float float1 = toSphere.getLength();
    float1 *= float1;
    if (float1 < float0) {
      return false;
    } else {
      float float2 = toSphere.dot3d(dirNormal);
      if (float2 < 0.0F) {
        return false;
      } else {
        float float3 = float0 + float2 * float2 - toSphere.getLength();
        return float3 >= 0.0;
      }
    }
  }
}
} // namespace util
} // namespace zombie
