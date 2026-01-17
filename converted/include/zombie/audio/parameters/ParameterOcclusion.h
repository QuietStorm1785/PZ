#pragma once
#include "fmod/fmod/FMODSoundEmitter.h"
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
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

class ParameterOcclusion : public FMODLocalParameter {
public:
  const FMODSoundEmitter emitter;
  float currentValue = Float.NaN;

public
  ParameterOcclusion(FMODSoundEmitter _emitter) {
    super("Occlusion");
    this.emitter = _emitter;
  }

  float calculateCurrentValue() {
    float float0 = 1.0F;

    for (int int0 = 0; int0 < 4; int0++) {
      float float1 = this.calculateValueForPlayer(int0);
      float0 = PZMath.min(float0, float1);
    }

    this.currentValue = float0;
    return (int)(this.currentValue * 1000.0F) / 1000.0F;
  }

  void resetToDefault() { this.currentValue = Float.NaN; }

  float calculateValueForPlayer(int int0) {
    IsoPlayer player = IsoPlayer.players[int0];
    if (player == nullptr) {
      return 1.0F;
    } else {
      IsoGridSquare square0 = player.getCurrentSquare();
      IsoGridSquare square1 = IsoWorld.instance.getCell().getGridSquare(
          (double)this.emitter.x, (double)this.emitter.y,
          (double)this.emitter.z);
      if (square1 == nullptr) {
        bool boolean0 = true;
      }

      float float0 = 0.0F;
      if (square0 != nullptr && square1 != nullptr &&
          !square1.isCouldSee(int0)) {
        float0 = 1.0F;
      }

      return float0;
    }
  }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
