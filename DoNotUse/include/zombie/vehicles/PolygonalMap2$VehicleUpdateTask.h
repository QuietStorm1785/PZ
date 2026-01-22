#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/PolygonalMap2/IVehicleTask.h"
#include "zombie/vehicles/PolygonalMap2/Vehicle.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    PolygonalMap2 map;
    BaseVehicle vehicle;
    const VehiclePoly poly = std::make_shared<VehiclePoly>();
    const VehiclePoly polyPlusRadius = std::make_shared<VehiclePoly>();
    float upVectorDot;
   static const ArrayDeque<PolygonalMap2$VehicleUpdateTask> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$VehicleUpdateTask() {
   }

    void init(PolygonalMap2 var1, BaseVehicle var2) {
      this.map = var1;
      this.vehicle = var2;
      this.poly.init(var2.getPoly());
      this.polyPlusRadius.init(var2.getPolyPlusRadius());
      this.upVectorDot = var2.getUpVectorDot();
   }

    void execute() {
    Vehicle var1 = (Vehicle)this.map.vehicleMap.get(this.vehicle);
      var1.poly.init(this.poly);
      var1.polyPlusRadius.init(this.polyPlusRadius);
      var1.upVectorDot = this.upVectorDot;
      this.vehicle = nullptr;
   }

   static PolygonalMap2$VehicleUpdateTask alloc() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         return pool.empty() ? new PolygonalMap2$VehicleUpdateTask() : pool.pop();
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
