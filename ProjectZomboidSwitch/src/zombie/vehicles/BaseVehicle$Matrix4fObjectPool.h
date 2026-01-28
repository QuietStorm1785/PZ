#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/mat4x4.hpp>
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    int allocated = 0;

   BaseVehicle$Matrix4fObjectPool() {
      super(Matrix4f::new);
   }

    Matrix4f makeObject() {
      this.allocated++;
      return (Matrix4f)super.makeObject();
   }
}
} // namespace vehicles
} // namespace zombie
