#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/Pool.h"
#include "zombie/vehicles/VehiclesDB2/QueueItem.h"

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
   static const Pool<VehiclesDB2$QueueRemoveVehicle> s_pool = std::make_shared<Pool>(VehiclesDB2$QueueRemoveVehicle::new);
    int m_id;

   private VehiclesDB2$QueueRemoveVehicle() {
   }

    void init(BaseVehicle var1) {
      this.m_id = var1.sqlID;
   }

    void processMain() {
   }

    void processWorldStreamer() {
      VehiclesDB2.instance.m_worldStreamer.m_store.removeVehicle(this.m_id);
   }
}
} // namespace vehicles
} // namespace zombie
