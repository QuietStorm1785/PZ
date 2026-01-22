#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/IVehicleTask.h"
#include "zombie/vehicles/PolygonalMap2/Vehicle.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    PolygonalMap2 map;
    BaseVehicle vehicle;
   static const ArrayDeque<PolygonalMap2$VehicleRemoveTask> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$VehicleRemoveTask() {
   }

    void init(PolygonalMap2 var1, BaseVehicle var2) {
      this.map = var1;
      this.vehicle = var2;
   }

    void execute() {
    Vehicle var1 = (Vehicle)this.map.vehicleMap.remove(this.vehicle);
      if (var1 != nullptr) {
         this.map.vehicles.remove(var1);
         var1.release();
      }

      this.vehicle = nullptr;
   }

   static PolygonalMap2$VehicleRemoveTask alloc() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         return pool.empty() ? new PolygonalMap2$VehicleRemoveTask() : pool.pop();
      }
   }

    void release() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         if (!$assertionsDisabled && pool.contains(this)) {
            throw std::make_unique<AssertionError>();
         } else {
            pool.push(this);
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
