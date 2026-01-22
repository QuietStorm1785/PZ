#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector3.h"

namespace zombie {
namespace util {


class RaySphereIntersectCheck {
public:
    static Vector3 toSphere = std::make_shared<Vector3>();
    static Vector3 dirNormal = std::make_shared<Vector3>();

    static bool intersects(Vector3 var0, Vector3 var1, Vector3 var2, float var3) {
      var3 *= var3;
      dirNormal.x = var1.x;
      dirNormal.y = var1.y;
      dirNormal.z = var1.z;
      dirNormal.normalize();
      toSphere.x = var2.x - var0.x;
      toSphere.y = var2.y - var0.y;
      toSphere.z = var2.z - var0.z;
    float var4 = toSphere.getLength();
      var4 *= var4;
      if (var4 < var3) {
    return false;
      } else {
    float var5 = toSphere.dot3d(dirNormal);
         if (var5 < 0.0F) {
    return false;
         } else {
    float var6 = var3 + var5 * var5 - toSphere.getLength();
            return var6 >= 0.0;
         }
      }
   }
}
} // namespace util
} // namespace zombie
