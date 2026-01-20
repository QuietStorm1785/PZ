#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace core {
namespace physics {


class CarController {
public:
    float engineForce;
    float brakingForce;
    float vehicleSteering;
    BaseVehicle vehicle;

   CarController$BulletVariables set(BaseVehicle var1, float var2, float var3, float var4) {
      this.vehicle = var1;
      this.engineForce = var2;
      this.brakingForce = var3;
      this.vehicleSteering = var4;
    return this;
   }
}
} // namespace physics
} // namespace core
} // namespace zombie
