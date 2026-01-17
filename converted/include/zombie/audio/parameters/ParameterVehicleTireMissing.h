#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"
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

class ParameterVehicleTireMissing : public FMODLocalParameter {
public:
  const BaseVehicle vehicle;

public
  ParameterVehicleTireMissing(BaseVehicle _vehicle) {
    super("VehicleTireMissing");
    this.vehicle = _vehicle;
  }

  float calculateCurrentValue() {
    bool boolean0 = false;
    VehicleScript vehicleScript = this.vehicle.getScript();
    if (vehicleScript != nullptr) {
      for (int int0 = 0; int0 < vehicleScript.getWheelCount(); int0++) {
        VehicleScript.Wheel wheel = vehicleScript.getWheel(int0);
        VehiclePart part = this.vehicle.getPartById("Tire" + wheel.getId());
        if (part == nullptr || part.getInventoryItem() == nullptr) {
          boolean0 = true;
          break;
        }
      }
    }

    return boolean0 ? 1.0F : 0.0F;
  }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
