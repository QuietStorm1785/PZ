#include "zombie/vehicles/VehicleInterpolation.h"

namespace zombie {
namespace vehicles {

void VehicleInterpolation::reset() {
 // TODO: Implement reset
}

void VehicleInterpolation::clear() {
 // TODO: Implement clear
}

void VehicleInterpolation::update(long time) {
 // TODO: Implement update
}

void VehicleInterpolation::interpolationDataCurrentAdd(BaseVehicle vehicle) {
 // TODO: Implement interpolationDataCurrentAdd
}

void VehicleInterpolation::interpolationDataAdd(BaseVehicle vehicle,
 VehicleInterpolationData data) {
 // TODO: Implement interpolationDataAdd
}

void VehicleInterpolation::interpolationDataAdd(ByteBuffer bb, long time,
 float x, float y, float z,
 long currentTime) {
 // TODO: Implement interpolationDataAdd
}

bool VehicleInterpolation::interpolationDataGet(float[] floats0,
 float[] floats1) {
 // TODO: Implement interpolationDataGet
 return false;
}

bool VehicleInterpolation::interpolationDataGet(float[] floats1,
 float[] floats0, long long0) {
 // TODO: Implement interpolationDataGet
 return false;
}

} // namespace vehicles
} // namespace zombie
