#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/audio/FMODLocalParameter.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterVehicleHitLocation : public FMODLocalParameter {
public:
 private ParameterVehicleHitLocation.HitLocation location = ParameterVehicleHitLocation.HitLocation.Front;

 public ParameterVehicleHitLocation() {
 super("VehicleHitLocation");
 }

 float calculateCurrentValue() {
 return this->location.label;
 }

 public static ParameterVehicleHitLocation.HitLocation calculateLocation(BaseVehicle vehicle, float x, float y, float z) {
 VehicleScript vehicleScript = vehicle.getScript();
 if (vehicleScript.empty()) {
 return ParameterVehicleHitLocation.HitLocation.Front;
 } else {
 Vector3f vector3f0 = vehicle.getLocalPos(x, y, z, BaseVehicle.TL_vector3f_pool.get().alloc());
 Vector3f vector3f1 = vehicleScript.getExtents();
 Vector3f vector3f2 = vehicleScript.getCenterOfMassOffset();
 float float0 = vector3f2.z - vector3f1.z / 2.0F;
 float float1 = vector3f2.z + vector3f1.z / 2.0F;
 float0 *= 0.9F;
 float1 *= 0.9F;
 ParameterVehicleHitLocation.HitLocation hitLocation;
 if (vector3f0.z >= float0 && vector3f0.z <= float1) {
 hitLocation = ParameterVehicleHitLocation.HitLocation.Side;
 } else if (vector3f0.z > 0.0F) {
 hitLocation = ParameterVehicleHitLocation.HitLocation.Front;
 } else {
 hitLocation = ParameterVehicleHitLocation.HitLocation.Rear;
 }

 BaseVehicle.TL_vector3f_pool.get().release(vector3f0);
 return hitLocation;
 }
 }

 void setLocation(ParameterVehicleHitLocation.HitLocation _location) {
 this->location = _location;
 }

 public static enum HitLocation {
 Front(0),
 Rear(1),
 Side(2);

 const int label;

 private HitLocation(int int1) {
 this->label = int1;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
