#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleBrake : public FMODLocalParameter {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleBrake(BaseVehicle var1) {
      super("VehicleBrake");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
      return this.vehicle.getController().isBrakePedalPressed() ? 1.0F : 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
