#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec3.hpp>
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    int allocated = 0;

   BaseVehicle$Vector3fObjectPool() {
      super(Vector3f::new);
   }

    Vector3f makeObject() {
      this.allocated++;
      return (Vector3f)super.makeObject();
   }
}
} // namespace vehicles
} // namespace zombie
