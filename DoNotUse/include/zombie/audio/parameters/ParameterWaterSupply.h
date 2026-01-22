#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SandboxOptions.h"
#include "zombie/audio/FMODGlobalParameter.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterWaterSupply : public FMODGlobalParameter {
public:
    public ParameterWaterSupply() {
      super("Water");
   }

    float calculateCurrentValue() {
      return GameTime.instance.NightsSurvived < SandboxOptions.instance.getWaterShutModifier() ? 1.0F : 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
