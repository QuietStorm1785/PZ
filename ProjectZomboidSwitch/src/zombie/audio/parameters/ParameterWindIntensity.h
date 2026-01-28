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


class ParameterWindIntensity : public OpenALParameterStub {
public:
    public ParameterWindIntensity() {
      super("WindIntensity");
   }

    float calculateCurrentValue() {
    float var1 = ClimateManager.getInstance().getWindIntensity();
      return (int)(var1 * 1000.0F) / 1000.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
