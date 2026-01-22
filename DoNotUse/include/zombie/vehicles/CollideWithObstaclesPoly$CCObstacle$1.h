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
#include "zombie/vehicles/CollideWithObstaclesPoly/CCObstacle.h"

namespace zombie {
namespace vehicles {


class CollideWithObstaclesPoly {
public:
   CollideWithObstaclesPoly$CCObstacle$1(Allocator var1) {
      super(var1);
   }

    void release(CCObstacle var1) {
      CCEdge.releaseAll(var1.outer);
      CCEdgeRing.releaseAll(var1.inner);
      var1.outer.clear();
      var1.inner.clear();
      var1.vehicle = nullptr;
      super.release(var1);
   }
}
} // namespace vehicles
} // namespace zombie
