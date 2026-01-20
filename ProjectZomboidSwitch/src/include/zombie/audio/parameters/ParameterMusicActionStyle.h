#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/audio/parameters/ParameterMusicActionStyle/State.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterMusicActionStyle : public FMODGlobalParameter {
public:
    public ParameterMusicActionStyle() {
      super("MusicActionStyle");
   }

    float calculateCurrentValue() {
      return Core.getInstance().getOptionMusicActionStyle() == 2 ? State.Legacy.label : State.Official.label;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
