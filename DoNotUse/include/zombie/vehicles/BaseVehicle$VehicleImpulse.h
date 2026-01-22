#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
   static const ArrayDeque<BaseVehicle$VehicleImpulse> pool = std::make_unique<ArrayDeque<>>();
    const Vector3f impulse = std::make_shared<Vector3f>();
    const Vector3f rel_pos = std::make_shared<Vector3f>();
    bool enable = false;

   private BaseVehicle$VehicleImpulse() {
   }

   static BaseVehicle$VehicleImpulse alloc() {
      return pool.empty() ? new BaseVehicle$VehicleImpulse() : pool.pop();
   }

    void release() {
      pool.push(this);
   }
}
} // namespace vehicles
} // namespace zombie
