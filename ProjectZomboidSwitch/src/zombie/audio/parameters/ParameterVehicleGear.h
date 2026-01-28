#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/parameters/OpenALParameterStub.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleGear : public zombie::audio::OpenALParameterStub {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleGear(BaseVehicle var1) {
      super("VehicleGear");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
      return this.vehicle.getTransmissionNumber() + 1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
