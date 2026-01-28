#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/iso/weather/ClimateManager.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterRainIntensity : public OpenALParameterStub {
public:
    public ParameterRainIntensity() {
      super("RainIntensity");
   }

    float calculateCurrentValue() {
      return ClimateManager.getInstance().isRaining() ? ClimateManager.getInstance().getPrecipitationIntensity() : 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
