#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by kroto on 1/17/2017.
 */
class VehicleInterpolationData {
public:
 long time;
 float x;
 float y;
 float z;
 float qx;
 float qy;
 float qz;
 float qw;
 float vx;
 float vy;
 float vz;
 float engineSpeed;
 float throttle;
 short wheelsCount = 4;
protected
 float[] wheelSteering = new float[4];
protected
 float[] wheelRotation = new float[4];
protected
 float[] wheelSkidInfo = new float[4];
protected
 float[] wheelSuspensionLength = new float[4];

 void setNumWheels(short short0) {
 if (short0 > this->wheelsCount) {
 this->wheelSteering = new float[short0];
 this->wheelRotation = new float[short0];
 this->wheelSkidInfo = new float[short0];
 this->wheelSuspensionLength = new float[short0];
 }

 this->wheelsCount = short0;
 }

 void copy(VehicleInterpolationData vehicleInterpolationData0) {
 this->time = vehicleInterpolationData0.time;
 this->x = vehicleInterpolationData0.x;
 this->y = vehicleInterpolationData0.y;
 this->z = vehicleInterpolationData0.z;
 this->qx = vehicleInterpolationData0.qx;
 this->qy = vehicleInterpolationData0.qy;
 this->qz = vehicleInterpolationData0.qz;
 this->qw = vehicleInterpolationData0.qw;
 this->vx = vehicleInterpolationData0.vx;
 this->vy = vehicleInterpolationData0.vy;
 this->vz = vehicleInterpolationData0.vz;
 this->engineSpeed = vehicleInterpolationData0.engineSpeed;
 this->throttle = vehicleInterpolationData0.throttle;
 this->setNumWheels(vehicleInterpolationData0.wheelsCount);

 for (int int0 = 0; int0 < vehicleInterpolationData0.wheelsCount; int0++) {
 this->wheelSteering[int0] = vehicleInterpolationData0.wheelSteering[int0];
 this->wheelRotation[int0] = vehicleInterpolationData0.wheelRotation[int0];
 this->wheelSkidInfo[int0] = vehicleInterpolationData0.wheelSkidInfo[int0];
 this->wheelSuspensionLength[int0] =
 vehicleInterpolationData0.wheelSuspensionLength[int0];
 }
 }

 int compareTo(VehicleInterpolationData o) {
 return Long.compare(this->time, o.time);
 }
}
} // namespace vehicles
} // namespace zombie
