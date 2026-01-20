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

enum class ParameterMusicLibrary {
   Official(0),
   EarlyAccess(1),
   Random(2);

    const int label;

   private ParameterMusicLibrary$Library(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
