#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/iso/weather/ClimateManager.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterWeatherEvent : public FMODGlobalParameter {
public:
 private ParameterWeatherEvent.Event event = ParameterWeatherEvent.Event.None;

 public ParameterWeatherEvent() {
 super("WeatherEvent");
 }

 float calculateCurrentValue() {
 float float0 = ClimateManager.getInstance().getSnowFracNow();
 if (!SandboxOptions.instance.EnableSnowOnGround.getValue()) {
 float0 = 0.0F;
 }

 return this->event.value;
 }

 public static enum Event {
 None(0),
 FreshSnow(1);

 const int value;

 private Event(int int1) {
 this->value = int1;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
