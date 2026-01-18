#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/WeatherPeriod.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterStorm : public FMODGlobalParameter {
public:
 public ParameterStorm() {
 super("Storm");
 }

 float calculateCurrentValue() {
 WeatherPeriod weatherPeriod = ClimateManager.getInstance().getWeatherPeriod();
 if (weatherPeriod.isRunning()) {
 if (weatherPeriod.isThunderStorm()) {
 return 1.0F;
 }

 if (weatherPeriod.isTropicalStorm()) {
 return 2.0F;
 }

 if (weatherPeriod.isBlizzard()) {
 return 3.0F;
 }
 }

 return 0.0F;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
