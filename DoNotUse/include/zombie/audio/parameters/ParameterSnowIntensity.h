#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/iso/weather/ClimateManager.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterSnowIntensity : public FMODGlobalParameter {
public:
    public ParameterSnowIntensity() {
      super("SnowIntensity");
   }

    float calculateCurrentValue() {
      return ClimateManager.getInstance().isSnowing() ? ClimateManager.getInstance().getPrecipitationIntensity() : 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
