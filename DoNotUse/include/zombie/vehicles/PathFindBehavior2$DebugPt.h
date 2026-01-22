#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class PathFindBehavior2 {
public:
    float x;
    float y;
    float z;
    bool climbing;

   private PathFindBehavior2$DebugPt() {
   }

   PathFindBehavior2$DebugPt init(float var1, float var2, float var3, boolean var4) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.climbing = var4;
    return this;
   }
}
} // namespace vehicles
} // namespace zombie
