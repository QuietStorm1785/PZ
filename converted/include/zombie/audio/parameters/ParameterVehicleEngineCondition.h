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
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterVehicleEngineCondition : public FMODLocalParameter {
public:
 const BaseVehicle vehicle;

 public ParameterVehicleEngineCondition(BaseVehicle _vehicle) {
 super("VehicleEngineCondition");
 this->vehicle = _vehicle;
 }

 float calculateCurrentValue() {
 VehiclePart part = this->vehicle.getPartById("Engine");
 return part = = nullptr ? 100.0F : PZMath.clamp(part.getCondition(), 0, 100);
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
