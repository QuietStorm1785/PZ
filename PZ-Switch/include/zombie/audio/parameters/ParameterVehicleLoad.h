#pragma once
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/vehicles/BaseVehicle.h"
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

class ParameterVehicleLoad : public FMODLocalParameter {
public:
 const BaseVehicle vehicle;

public
 ParameterVehicleLoad(BaseVehicle _vehicle) {
 super("VehicleLoad");
 this->vehicle = _vehicle;
 }

 float calculateCurrentValue() {
 return this->vehicle.getController().isGasPedalPressed() ? 1.0F : 0.0F;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
