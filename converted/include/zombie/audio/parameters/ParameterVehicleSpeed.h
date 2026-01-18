#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterVehicleSpeed : public FMODLocalParameter {
public:
 const BaseVehicle vehicle;

 public ParameterVehicleSpeed(BaseVehicle _vehicle) {
 super("VehicleSpeed");
 this->vehicle = _vehicle;
 }

 float calculateCurrentValue() {
 return (float)Math.floor(Math.abs(this->vehicle.getCurrentSpeedKmHour()));
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
