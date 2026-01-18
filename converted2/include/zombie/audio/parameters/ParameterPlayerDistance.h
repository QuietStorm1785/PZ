#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/math/PZMath.h"
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

class ParameterPlayerDistance : public FMODLocalParameter {
public:
  const IsoZombie zombie;

public
  ParameterPlayerDistance(IsoZombie _zombie) {
    super("PlayerDistance");
    this.zombie = _zombie;
  }

  float calculateCurrentValue() {
    return this.zombie.target == nullptr
               ? 1000.0F
               : (int)PZMath.ceil(this.zombie.DistToProper(this.zombie.target));
  }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
