#pragma once
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

class ParameterSnowIntensity : public FMODGlobalParameter {
public:
public
 ParameterSnowIntensity() { super("SnowIntensity"); }

 float calculateCurrentValue() {
 return ClimateManager.getInstance().isSnowing()
 ? ClimateManager.getInstance().getPrecipitationIntensity()
 : 0.0F;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
