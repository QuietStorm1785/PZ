#pragma once
#include "zombie/GameTime.h"
#include "zombie/SandboxOptions.h"
#include "zombie/audio/FMODGlobalParameter.h"
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

class ParameterWaterSupply : public FMODGlobalParameter {
public:
public
 ParameterWaterSupply() { super("Water"); }

 float calculateCurrentValue() {
 return GameTime.instance.NightsSurvived <
 SandboxOptions.instance.getWaterShutModifier()
 ? 1.0F
 : 0.0F;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
