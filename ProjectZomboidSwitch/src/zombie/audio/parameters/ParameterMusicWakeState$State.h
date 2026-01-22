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

enum class ParameterMusicWakeState {
   Awake(0),
   Sleeping(1),
   WakeNormal(2),
   WakeNightmare(3),
   WakeZombies(4);

    const int label;

   private ParameterMusicWakeState$State(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
