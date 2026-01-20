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

enum class ParameterCharacterMovementSpeed {
   SneakWalk(0),
   SneakRun(1),
   Strafe(2),
   Walk(3),
   Run(4),
   Sprint(5);

    const int label;

   private ParameterCharacterMovementSpeed$MovementType(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
