#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
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
    const TFloatArrayList crawlOffsets = std::make_shared<TFloatArrayList>();
    float upVectorDot;
   static const ArrayDeque<PolygonalMap2$VehicleAddTask> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$VehicleAddTask() {
   }

    void init(PolygonalMap2 var1, BaseVehicle var2) {
      this.map = var1;
      this.vehicle = var2;
      this.poly.init(var2.getPoly());
      this.polyPlusRadius.init(var2.getPolyPlusRadius());
      this.crawlOffsets.resetQuick();
      this.crawlOffsets.addAll(var2.getScript().getCrawlOffsets());
      this.upVectorDot = var2.getUpVectorDot();
   }

    void execute() {
    Vehicle var1 = Vehicle.alloc();
      var1.poly.init(this.poly);
      var1.polyPlusRadius.init(this.polyPlusRadius);
      var1.crawlOffsets.resetQuick();
      var1.crawlOffsets.addAll(this.crawlOffsets);
      var1.upVectorDot = this.upVectorDot;
      this.map.vehicles.push_back(var1);
      this.map.vehicleMap.put(this.vehicle, var1);
      this.vehicle = nullptr;
   }

   static PolygonalMap2$VehicleAddTask alloc() {
      /* synchronized - TODO: add std::mutex */ (pool) {
         return pool.empty() ? new PolygonalMap2$VehicleAddTask() : pool.pop();
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
