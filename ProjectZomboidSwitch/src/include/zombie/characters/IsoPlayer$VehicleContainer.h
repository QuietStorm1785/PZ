#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace characters {


class IsoPlayer {
public:
    BaseVehicle vehicle;
    int containerIndex;

   private IsoPlayer$VehicleContainer() {
   }

   public IsoPlayer$VehicleContainer set(BaseVehicle var1, int var2) {
      this.vehicle = var1;
      this.containerIndex = var2;
    return this;
   }

    bool equals(void* var1) {
      return dynamic_cast<IsoPlayer*>(var1) != nullptr$VehicleContainer
         && this.vehicle == ((IsoPlayer$VehicleContainer)var1).vehicle
         && this.containerIndex == ((IsoPlayer$VehicleContainer)var1).containerIndex;
   }
}
} // namespace characters
} // namespace zombie
