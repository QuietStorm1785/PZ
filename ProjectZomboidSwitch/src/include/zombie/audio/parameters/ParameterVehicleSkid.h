#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/network/GameClient.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/WheelInfo.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleSkid : public FMODLocalParameter {
public:
    const BaseVehicle vehicle;
   private const WheelInfo[] wheelInfo;

    public ParameterVehicleSkid(BaseVehicle var1) {
      super("VehicleSkid");
      this.vehicle = var1;
      this.wheelInfo = var1.wheelInfo;
   }

    float calculateCurrentValue() {
    float var1 = 1.0F;
      if (GameClient.bClient && !this.vehicle.isLocalPhysicSim()) {
    return var1;
      } else {
    VehicleScript var2 = this.vehicle.getScript();
         if (var2 == nullptr) {
    return var1;
         } else {
    int var3 = 0;

            for (int var4 = var2.getWheelCount(); var3 < var4; var3++) {
               var1 = PZMath.min(var1, this.wheelInfo[var3].skidInfo);
            }

            return (int)(100.0F - PZMath.clamp(var1, 0.0F, 1.0F) * 100.0F) / 100.0F;
         }
      }
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
