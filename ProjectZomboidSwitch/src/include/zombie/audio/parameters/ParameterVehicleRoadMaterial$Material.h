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

enum class ParameterVehicleRoadMaterial {
   Concrete(0),
   Grass(1),
   Gravel(2),
   Puddle(3),
   Snow(4),
   Wood(5),
   Carpet(6),
   Dirt(7),
   Sand(8);

    const int label;

   private ParameterVehicleRoadMaterial$Material(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
