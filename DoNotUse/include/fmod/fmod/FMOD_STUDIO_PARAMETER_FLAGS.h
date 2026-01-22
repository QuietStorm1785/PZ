#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

enum class FMOD_STUDIO_PARAMETER_FLAGS {
   FMOD_STUDIO_PARAMETER_READONLY(1),
   FMOD_STUDIO_PARAMETER_AUTOMATIC(2),
   FMOD_STUDIO_PARAMETER_GLOBAL(4),
   FMOD_STUDIO_PARAMETER_DISCRETE(8);

    const int bit;

    private FMOD_STUDIO_PARAMETER_FLAGS(int var3) {
      this.bit = var3;
   }
}
} // namespace fmod
} // namespace fmod
