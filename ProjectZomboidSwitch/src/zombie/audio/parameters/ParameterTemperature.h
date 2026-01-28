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


class ParameterTemperature : public OpenALParameterStub {
public:
    public ParameterTemperature() {
      super("Temperature");
   }

    float calculateCurrentValue() {
      return (int)(ClimateManager.getInstance().getTemperature() * 100.0F) / 100.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
