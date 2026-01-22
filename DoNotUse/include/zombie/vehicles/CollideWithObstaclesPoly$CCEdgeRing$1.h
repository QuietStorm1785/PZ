#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool.h"
#include "zombie/popman/ObjectPool/Allocator.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdge.h"
#include "zombie/vehicles/CollideWithObstaclesPoly/CCEdgeRing.h"

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
   CollideWithObstaclesPoly$CCEdgeRing$1(Allocator var1) {
      super(var1);
   }

    void release(CCEdgeRing var1) {
      CCEdge.releaseAll(var1);
      this.clear();
      super.release(var1);
   }
}
} // namespace vehicles
} // namespace zombie
