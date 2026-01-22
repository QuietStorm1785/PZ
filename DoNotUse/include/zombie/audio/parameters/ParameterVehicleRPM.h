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

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleRPM : public FMODLocalParameter {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleRPM(BaseVehicle var1) {
      super("VehicleRPM");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
    float var1 = PZMath.clamp((float)this.vehicle.getEngineSpeed(), 0.0F, 7000.0F);
    float var2 = this.vehicle.getScript().getEngineIdleSpeed();
    float var3 = var2 * 1.1F;
    float var5 = 800.0F;
    float var6 = 7000.0F;
    float var4;
      if (var1 < var3) {
         var4 = var1 / var3 * var5;
      } else {
         var4 = var5 + (var1 - var3) / (7000.0F - var3) * (var6 - var5);
      }

      return (int)((var4 + 50.0F - 1.0F) / 50.0F) * 50.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
