#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec3.hpp>
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class PolygonalMap2 {
public:
    BaseVehicle vehicle;
    float x;
    float y;
    float z;
    const Vector3f forward = std::make_shared<Vector3f>();
    const VehiclePoly polyPlusRadius = std::make_shared<VehiclePoly>();
   static const ArrayDeque<PolygonalMap2$VehicleState> pool = std::make_unique<ArrayDeque<>>();

   private PolygonalMap2$VehicleState() {
   }

   PolygonalMap2$VehicleState init(BaseVehicle var1) {
      this.vehicle = var1;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      var1.getForwardVector(this.forward);
      this.polyPlusRadius.init(var1.getPolyPlusRadius());
    return this;
   }

    bool check() {
    bool var1 = this.x != this.vehicle.x || this.y != this.vehicle.y || (int)this.z != (int)this.vehicle.z;
      if (!var1) {
    Vector3fObjectPool var2 = (Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get();
    Vector3f var3 = this.vehicle.getForwardVector((Vector3f)var2.alloc());
         var1 = this.forward.dot(var3) < 0.999F;
         if (var1) {
            this.forward.set(var3);
         }

         var2.release(var3);
      }

      if (var1) {
         this.x = this.vehicle.x;
         this.y = this.vehicle.y;
         this.z = this.vehicle.z;
      }

    return var1;
   }

   static PolygonalMap2$VehicleState alloc() {
      return pool.empty() ? new PolygonalMap2$VehicleState() : pool.pop();
   }

    void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw std::make_unique<AssertionError>();
      } else {
         pool.push(this);
      }
   }
}
} // namespace vehicles
} // namespace zombie
