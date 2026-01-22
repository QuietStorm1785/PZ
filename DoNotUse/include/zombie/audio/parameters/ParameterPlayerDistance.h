#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterPlayerDistance : public FMODLocalParameter {
public:
    const IsoZombie zombie;

    public ParameterPlayerDistance(IsoZombie var1) {
      super("PlayerDistance");
      this.zombie = var1;
   }

    float calculateCurrentValue() {
      return this.zombie.target == nullptr ? 1000.0F : (int)PZMath.ceil(this.zombie.DistToProper(this.zombie.target));
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
