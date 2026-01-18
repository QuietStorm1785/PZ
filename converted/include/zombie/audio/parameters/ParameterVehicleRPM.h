#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterVehicleRPM : public FMODLocalParameter {
public:
 const BaseVehicle vehicle;

 public ParameterVehicleRPM(BaseVehicle _vehicle) {
 super("VehicleRPM");
 this->vehicle = _vehicle;
 }

 float calculateCurrentValue() {
 float float0 = PZMath.clamp((float)this->vehicle.getEngineSpeed(), 0.0F, 7000.0F);
 float float1 = this->vehicle.getScript().getEngineIdleSpeed();
 float float2 = float1 * 1.1F;
 float float3 = 800.0F;
 float float4 = 7000.0F;
 float float5;
 if (float0 < float2) {
 float5 = float0 / float2 * float3;
 } else {
 float5 = float3 + (float0 - float2) / (7000.0F - float2) * (float4 - float3);
 }

 return (int)((float5 + 50.0F - 1.0F) / 50.0F) * 50.0F;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
