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
#include "zombie/vehicles/VehiclesDB2/VehicleBuffer.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclesDB2 {
public:
   static const Pool<VehiclesDB2$QueueAddVehicle> s_pool = std::make_shared<Pool>(VehiclesDB2$QueueAddVehicle::new);
    const VehicleBuffer m_vehicleBuffer = std::make_shared<VehicleBuffer>();

   private VehiclesDB2$QueueAddVehicle() {
   }

    void init(BaseVehicle var1) {
      this.m_vehicleBuffer.set(var1);
   }

    void processMain() {
   }

    void processWorldStreamer() {
      VehiclesDB2.instance.m_worldStreamer.m_store.updateVehicle(this.m_vehicleBuffer);
   }
}
} // namespace vehicles
} // namespace zombie
