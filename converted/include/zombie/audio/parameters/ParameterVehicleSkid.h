#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/network/GameClient.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterVehicleSkid : public FMODLocalParameter {
public:
 const BaseVehicle vehicle;
 private BaseVehicle.WheelInfo[] wheelInfo;

 public ParameterVehicleSkid(BaseVehicle _vehicle) {
 super("VehicleSkid");
 this->vehicle = _vehicle;
 this->wheelInfo = _vehicle.wheelInfo;
 }

 float calculateCurrentValue() {
 float float0 = 1.0F;
 if (GameClient.bClient && !this->vehicle.isLocalPhysicSim()) {
 return float0;
 } else {
 VehicleScript vehicleScript = this->vehicle.getScript();
 if (vehicleScript == nullptr) {
 return float0;
 } else {
 int int0 = 0;

 for (int int1 = vehicleScript.getWheelCount(); int0 < int1; int0++) {
 float0 = PZMath.min(float0, this->wheelInfo[int0].skidInfo);
 }

 return (int)(100.0F - PZMath.clamp(float0, 0.0F, 1.0F) * 100.0F) / 100.0F;
 }
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
