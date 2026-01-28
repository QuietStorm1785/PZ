#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/parameters/OpenALParameterStub.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterPlayerHealth : public zombie::audio::OpenALParameterStub {
public:
    const IsoPlayer player;

    public ParameterPlayerHealth(IsoPlayer var1) {
      super("PlayerHealth");
      this.player = var1;
   }

    float calculateCurrentValue() {
      return PZMath.clamp(this.player.getHealth() / 100.0F, 0.0F, 1.0F);
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
