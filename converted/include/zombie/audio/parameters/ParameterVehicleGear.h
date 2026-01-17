#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterVehicleGear : public FMODLocalParameter {
public:
  const BaseVehicle vehicle;

public
  ParameterVehicleGear(BaseVehicle _vehicle) {
    super("VehicleGear");
    this.vehicle = _vehicle;
  }

  float calculateCurrentValue() {
    return this.vehicle.getTransmissionNumber() + 1;
  }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
