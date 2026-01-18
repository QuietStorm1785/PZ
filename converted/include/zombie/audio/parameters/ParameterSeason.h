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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterSeason : public FMODGlobalParameter {
public:
 public ParameterSeason() {
 super("Season");
 }

 float calculateCurrentValue() {
 ClimateManager.DayInfo dayInfo = ClimateManager.getInstance().getCurrentDay();
 if (dayInfo == nullptr) {
 return 0.0F;
 } else {
 return switch() {
 case 1 -> 0.0F;
 case 2, 3 -> 1.0F;
 case 4 -> 2.0F;
 case 5 -> 3.0F;
 default -> 1.0F;
 };
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
