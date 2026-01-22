#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterPowerSupply : public FMODGlobalParameter {
public:
    public ParameterPowerSupply() {
      super("Electricity");
   }

    float calculateCurrentValue() {
      return IsoWorld.instance != nullptr && IsoWorld.instance.isHydroPowerOn() ? 1.0F : 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
