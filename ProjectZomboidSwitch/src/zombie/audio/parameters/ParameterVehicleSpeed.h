#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleSpeed : public OpenALParameterStub {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleSpeed(BaseVehicle var1) {
      super("VehicleSpeed");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
      return (float)Math.floor(Math.abs(this.vehicle.getCurrentSpeedKmHour()));
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
