#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/PooledObject.h"

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
   private VehiclesDB2$QueueItem() {
   }

   abstract void processMain();

   abstract void processWorldStreamer();
}
} // namespace vehicles
} // namespace zombie
