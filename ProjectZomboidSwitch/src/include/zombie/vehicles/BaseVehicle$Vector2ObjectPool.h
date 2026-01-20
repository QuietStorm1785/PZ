#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/Vector2.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    int allocated = 0;

   BaseVehicle$Vector2ObjectPool() {
      super(Vector2::new);
   }

    Vector2 makeObject() {
      this.allocated++;
      return (Vector2)super.makeObject();
   }
}
} // namespace vehicles
} // namespace zombie
