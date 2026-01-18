#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/objects/VehicleScript.h"
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

class ParameterVehicleSteer : public FMODLocalParameter {
public:
  const BaseVehicle vehicle;

public
  ParameterVehicleSteer(BaseVehicle _vehicle) {
    super("VehicleSteer");
    this.vehicle = _vehicle;
  }

  float calculateCurrentValue() {
    float float0 = 0.0F;
    if (!this.vehicle.isEngineRunning()) {
      return float0;
    } else {
      VehicleScript vehicleScript = this.vehicle.getScript();
      if (vehicleScript == nullptr) {
        return float0;
      } else {
        BaseVehicle.WheelInfo[] wheelInfos = this.vehicle.wheelInfo;
        int int0 = 0;

        for (int int1 = vehicleScript.getWheelCount(); int0 < int1; int0++) {
          float0 = PZMath.max(float0, Math.abs(wheelInfos[int0].steering));
        }

        return (int)(PZMath.clamp(float0, 0.0F, 1.0F) * 100.0F) / 100.0F;
      }
    }
  }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
