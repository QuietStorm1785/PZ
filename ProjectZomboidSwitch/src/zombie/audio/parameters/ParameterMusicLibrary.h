#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterMusicLibrary/Library.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterMusicLibrary : public OpenALParameterStub {
public:
    public ParameterMusicLibrary() {
      super("MusicLibrary");
   }

    float calculateCurrentValue() {
    return switch() {
         case 2 -> Library.EarlyAccess.label;
         case 3 -> Library.Random.label;
         default -> Library.Official.label;
      };
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
