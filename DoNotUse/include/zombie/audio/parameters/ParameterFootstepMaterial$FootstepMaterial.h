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

enum class ParameterFootstepMaterial {
   Upstairs(0),
   BrokenGlass(1),
   Concrete(2),
   Grass(3),
   Gravel(4),
   Puddle(5),
   Snow(6),
   Wood(7),
   Carpet(8),
   Dirt(9),
   Sand(10),
   Ceramic(11),
   Metal(12);

    const int label;

   private ParameterFootstepMaterial$FootstepMaterial(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
