#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Quaternionf.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    int allocated = 0;

   BaseVehicle$QuaternionfObjectPool() {
      super(Quaternionf::new);
   }

    Quaternionf makeObject() {
      this.allocated++;
      return (Quaternionf)super.makeObject();
   }
}
} // namespace vehicles
} // namespace zombie
