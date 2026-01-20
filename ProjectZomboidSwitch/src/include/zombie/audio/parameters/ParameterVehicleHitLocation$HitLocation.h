#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace audio {
namespace parameters {

enum class ParameterVehicleHitLocation {
   Front(0),
   Rear(1),
   Side(2);

    const int label;

   private ParameterVehicleHitLocation$HitLocation(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
