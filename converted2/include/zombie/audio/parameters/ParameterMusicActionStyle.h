#pragma once
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/core/Core.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterMusicActionStyle : public FMODGlobalParameter {
public:
public
  ParameterMusicActionStyle() { super("MusicActionStyle"); }

  float calculateCurrentValue() {
    return Core.getInstance().getOptionMusicActionStyle() == 2
               ? ParameterMusicActionStyle.State.Legacy.label
               : ParameterMusicActionStyle.State.Official.label;
  }

public
  static enum State {
    Official(0), Legacy(1);

    const int label;

    private State(int int1){this.label = int1;}
}
} // namespace parameters
} // namespace audio
} // namespace zombie
} // namespace zombie
