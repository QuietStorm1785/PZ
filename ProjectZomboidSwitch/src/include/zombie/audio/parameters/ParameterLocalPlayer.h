#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterLocalPlayer : public FMODLocalParameter {
public:
    const IsoPlayer player;

    public ParameterLocalPlayer(IsoPlayer var1) {
      super("LocalPlayer");
      this.player = var1;
   }

    float calculateCurrentValue() {
      return this.player.isLocalPlayer() ? 1.0F : 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
