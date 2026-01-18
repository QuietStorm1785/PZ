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


class ParameterVehicleBrake : public FMODLocalParameter {
public:
 const BaseVehicle vehicle;

 public ParameterVehicleBrake(BaseVehicle _vehicle) {
 super("VehicleBrake");
 this->vehicle = _vehicle;
 }

 float calculateCurrentValue() {
 return this->vehicle.getController().isBrakePedalPressed() ? 1.0F : 0.0F;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
