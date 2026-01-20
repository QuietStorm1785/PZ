#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class PolygonalMap2 {
public:
    float x;
    float y;
    float z;
    int flags;

   PolygonalMap2$PathNode init(float var1, float var2, float var3, int var4) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.flags = var4;
    return this;
   }

   PolygonalMap2$PathNode init(PolygonalMap2$PathNode var1) {
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.flags = var1.flags;
    return this;
   }

    bool hasFlag(int var1) {
      return (this.flags & var1) != 0;
   }
}
} // namespace vehicles
} // namespace zombie
