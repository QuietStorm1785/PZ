#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/audio/OpenALParameterStub.h"
#include "zombie/audio/parameters/ParameterWeatherEvent/Event.h"
#include "zombie/iso/weather/ClimateManager.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterWeatherEvent : public OpenALParameterStub {
public:
    Event event = Event.None;

    public ParameterWeatherEvent() {
      super("WeatherEvent");
   }

    float calculateCurrentValue() {
    float var1 = ClimateManager.getInstance().getSnowFracNow();
      if (!SandboxOptions.instance.EnableSnowOnGround.getValue()) {
         var1 = 0.0F;
      }

      return this.event.value;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
