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

enum class ParameterCurrentZone {
   None(0),
   DeepForest(1),
   Farm(2),
   Forest(3),
   Nav(4),
   Town(5),
   TrailerPark(6),
   Vegetation(7);

    const int label;

   private ParameterCurrentZone$Zone(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
