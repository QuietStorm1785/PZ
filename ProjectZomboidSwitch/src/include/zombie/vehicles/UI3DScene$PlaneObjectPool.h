#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/UI3DScene/Plane.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    int allocated = 0;

   public UI3DScene$PlaneObjectPool() {
      super(Plane::new);
   }

    Plane makeObject() {
      this.allocated++;
      return (Plane)super.makeObject();
   }
}
} // namespace vehicles
} // namespace zombie
