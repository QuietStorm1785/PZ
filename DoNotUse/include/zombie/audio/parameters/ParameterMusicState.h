#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/audio/parameters/ParameterMusicState/State.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterMusicState : public FMODGlobalParameter {
public:
    State state = State.MainMenu;

    public ParameterMusicState() {
      super("MusicState");
   }

    float calculateCurrentValue() {
      return this.state.label;
   }

    void setState(State var1) {
      this.state = var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
