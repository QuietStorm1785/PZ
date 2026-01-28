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


class ParameterFogIntensity : public OpenALParameterStub {
public:
    public ParameterFogIntensity() {
      super("FogIntensity");
   }

    float calculateCurrentValue() {
      return ClimateManager.getInstance().getFogIntensity();
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
