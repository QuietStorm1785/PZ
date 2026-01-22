#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleEngineCondition : public FMODLocalParameter {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleEngineCondition(BaseVehicle var1) {
      super("VehicleEngineCondition");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
    VehiclePart var1 = this.vehicle.getPartById("Engine");
    return var1 = = nullptr ? 100.0F : PZMath.clamp(var1.getCondition(), 0, 100);
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
