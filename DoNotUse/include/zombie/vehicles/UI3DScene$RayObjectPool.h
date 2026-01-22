#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/popman/ObjectPool.h"
#include "zombie/vehicles/UI3DScene/Ray.h"

namespace zombie {
namespace vehicles {


class UI3DScene {
public:
    int allocated = 0;

   public UI3DScene$RayObjectPool() {
      super(Ray::new);
   }

    Ray makeObject() {
      this.allocated++;
      return (Ray)super.makeObject();
   }
}
} // namespace vehicles
} // namespace zombie
