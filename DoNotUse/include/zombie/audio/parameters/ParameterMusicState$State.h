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

enum class ParameterMusicState {
   MainMenu(0),
   Loading(1),
   InGame(2),
   PauseMenu(3),
   Tutorial(4);

    const int label;

   private ParameterMusicState$State(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
