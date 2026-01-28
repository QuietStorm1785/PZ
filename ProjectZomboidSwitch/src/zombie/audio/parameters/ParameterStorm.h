#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/WeatherPeriod.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterStorm : public OpenALParameterStub {
public:
    public ParameterStorm() {
      super("Storm");
   }

    float calculateCurrentValue() {
    WeatherPeriod var1 = ClimateManager.getInstance().getWeatherPeriod();
      if (var1.isRunning()) {
         if (var1.isThunderStorm()) {
            return 1.0F;
         }

         if (var1.isTropicalStorm()) {
            return 2.0F;
         }

         if (var1.isBlizzard()) {
            return 3.0F;
         }
      }

      return 0.0F;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
