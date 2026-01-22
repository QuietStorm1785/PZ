#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/Point.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
   const ArrayDeque<Point> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$PointPool() {
   }

    Point alloc() {
      return this.pool.empty() ? std::make_unique<Point>() : this.pool.pop();
   }

    void release(Point var1) {
      this.pool.push(var1);
   }
}
} // namespace vehicles
} // namespace zombie
