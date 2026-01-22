#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    int allocated = 0;

   BaseVehicle$Vector2fObjectPool() {
      super(Vector2f::new);
   }

    Vector2f makeObject() {
      this.allocated++;
      return (Vector2f)super.makeObject();
   }
}
} // namespace vehicles
} // namespace zombie
