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

enum class ParameterFootstepMaterial2 {
   None(0),
   BrokenGlass(1),
   PuddleShallow(2),
   PuddleDeep(3);

    const int label;

   private ParameterFootstepMaterial2$FootstepMaterial2(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
