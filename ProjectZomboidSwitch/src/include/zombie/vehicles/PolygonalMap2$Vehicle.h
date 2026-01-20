#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    const VehiclePoly poly = std::make_shared<VehiclePoly>();
    const VehiclePoly polyPlusRadius = std::make_shared<VehiclePoly>();
    const TFloatArrayList crawlOffsets = std::make_shared<TFloatArrayList>();
    float upVectorDot;
   static const ArrayDeque<PolygonalMap2$Vehicle> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$Vehicle() {
   }

   static PolygonalMap2$Vehicle alloc() {
      return pool.empty() ? new PolygonalMap2$Vehicle() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
