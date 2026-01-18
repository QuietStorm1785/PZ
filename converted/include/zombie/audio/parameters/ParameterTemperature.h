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


class ParameterTemperature : public FMODGlobalParameter {
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
