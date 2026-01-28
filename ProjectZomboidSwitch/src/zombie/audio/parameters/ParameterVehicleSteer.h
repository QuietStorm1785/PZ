#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/WheelInfo.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleSteer : public OpenALParameterStub {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleSteer(BaseVehicle var1) {
      super("VehicleSteer");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
    float var1 = 0.0F;
      if (!this.vehicle.isEngineRunning()) {
    return var1;
      } else {
    VehicleScript var2 = this.vehicle.getScript();
         if (var2 == nullptr) {
    return var1;
         } else {
            WheelInfo[] var3 = this.vehicle.wheelInfo;
    int var4 = 0;

            for (int var5 = var2.getWheelCount(); var4 < var5; var4++) {
               var1 = PZMath.max(var1, Math.abs(var3[var4].steering));
            }

            return (int)(PZMath.clamp(var1, 0.0F, 1.0F) * 100.0F) / 100.0F;
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
