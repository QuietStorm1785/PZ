#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/parameters/OpenALParameterStub.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterVehicleTireMissing : public zombie::audio::OpenALParameterStub {
public:
    const BaseVehicle vehicle;

    public ParameterVehicleTireMissing(BaseVehicle var1) {
      super("VehicleTireMissing");
      this.vehicle = var1;
   }

    float calculateCurrentValue() {
    bool var1 = false;
    VehicleScript var2 = this.vehicle.getScript();
      if (var2 != nullptr) {
         for (int var3 = 0; var3 < var2.getWheelCount(); var3++) {
    Wheel var4 = var2.getWheel(var3);
    VehiclePart var5 = this.vehicle.getPartById("Tire" + var4.getId());
            if (var5 == nullptr || var5.getInventoryItem() == nullptr) {
               var1 = true;
               break;
            }
         }
      }

      return var1 ? 1.0F : 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
