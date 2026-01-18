#pragma once
#include "zombie/GameTime.h"
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/iso/weather/ClimateManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ParameterTimeOfDay : public FMODGlobalParameter {
public:
public
 ParameterTimeOfDay() { super("TimeOfDay"); }

 float calculateCurrentValue() {
 ClimateManager.DayInfo dayInfo =
 ClimateManager.getInstance().getCurrentDay();
 if (dayInfo.empty()) {
 return 1.0F;
 } else {
 float float0 = dayInfo.season.getDawn();
 float float1 = dayInfo.season.getDusk();
 float float2 = dayInfo.season.getDayHighNoon();
 float float3 = GameTime.instance.getTimeOfDay();
 if (float3 >= float0 - 1.0F && float3 < float0 + 1.0F) {
 return 0.0F;
 } else if (float3 >= float0 + 1.0F && float3 < float0 + 2.0F) {
 return 1.0F;
 } else if (float3 >= float0 + 2.0F && float3 < float1 - 2.0F) {
 return 2.0F;
 } else if (float3 >= float1 - 2.0F && float3 < float1 - 1.0F) {
 return 3.0F;
 } else {
 return float3 >= float1 - 1.0F && float3 < float1 + 1.0F ? 4.0F : 5.0F;
 }
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
