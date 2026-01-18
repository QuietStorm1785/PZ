#pragma once
#include "org/joml/Quaternionf.h"
#include "zombie/GameTime.h"
#include "zombie/core/physics/WorldSimulation.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
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
class VehicleInterpolation {
public:
 int delay;
 int history;
 bool buffering;
private
 static ArrayDeque<VehicleInterpolationData> pool =
 std::make_unique<ArrayDeque<>>();
private
 static List<VehicleInterpolationData> outdated =
 std::make_unique<ArrayList<>>();
 TreeSet<VehicleInterpolationData> buffer = std::make_unique<TreeSet<>>();
 static const Quaternionf tempQuaternionA = new Quaternionf();
 static const Quaternionf tempQuaternionB = new Quaternionf();
 static const VehicleInterpolationData temp = new VehicleInterpolationData();

 VehicleInterpolation() {
 this->reset();
 this->delay = 500;
 this->history = 800;
 }

 void reset() {
 this->buffering = true;
 this->clear();
 }

 void clear() {
 if (!this->buffer.empty()) {
 pool.addAll(this->buffer);
 this->buffer.clear();
 outdated.clear();
 }
 }

 void update(long time) {
 temp.time = time - this->delay;
 VehicleInterpolationData vehicleInterpolationData0 =
 this->buffer.floor(temp);

 for (VehicleInterpolationData vehicleInterpolationData1 : this->buffer) {
 if (time - vehicleInterpolationData1.time > this->history &&
 vehicleInterpolationData1 != vehicleInterpolationData0) {
 outdated.add(vehicleInterpolationData1);
 }
 }

 outdated.forEach(this->buffer::remove);
 pool.addAll(outdated);
 outdated.clear();
 if (this->buffer.empty()) {
 this->buffering = true;
 }
 }

 void interpolationDataCurrentAdd(BaseVehicle vehicle) {
 VehicleInterpolationData vehicleInterpolationData =
 pool.empty() ? new VehicleInterpolationData() : pool.pop();
 vehicleInterpolationData.time = GameTime.getServerTimeMills() - this->delay;
 vehicleInterpolationData.x =
 vehicle.jniTransform.origin.x + WorldSimulation.instance.offsetX;
 vehicleInterpolationData.y =
 vehicle.jniTransform.origin.z + WorldSimulation.instance.offsetY;
 vehicleInterpolationData.z = vehicle.jniTransform.origin.y;
 Quaternionf quaternionf =
 vehicle.jniTransform.getRotation(new Quaternionf());
 vehicleInterpolationData.qx = quaternionf.x;
 vehicleInterpolationData.qy = quaternionf.y;
 vehicleInterpolationData.qz = quaternionf.z;
 vehicleInterpolationData.qw = quaternionf.w;
 vehicleInterpolationData.vx = vehicle.jniLinearVelocity.x;
 vehicleInterpolationData.vy = vehicle.jniLinearVelocity.y;
 vehicleInterpolationData.vz = vehicle.jniLinearVelocity.z;
 vehicleInterpolationData.engineSpeed = (float)vehicle.engineSpeed;
 vehicleInterpolationData.throttle = vehicle.throttle;
 vehicleInterpolationData.setNumWheels((short)vehicle.wheelInfo.length);

 for (int int0 = 0; int0 < vehicleInterpolationData.wheelsCount; int0++) {
 vehicleInterpolationData.wheelSteering[int0] =
 vehicle.wheelInfo[int0].steering;
 vehicleInterpolationData.wheelRotation[int0] =
 vehicle.wheelInfo[int0].rotation;
 vehicleInterpolationData.wheelSkidInfo[int0] =
 vehicle.wheelInfo[int0].skidInfo;
 vehicleInterpolationData.wheelSuspensionLength[int0] =
 vehicle.wheelInfo[int0].suspensionLength;
 }

 this->buffer.add(vehicleInterpolationData);
 }

 void interpolationDataAdd(BaseVehicle vehicle,
 VehicleInterpolationData data) {
 VehicleInterpolationData vehicleInterpolationData =
 pool.empty() ? new VehicleInterpolationData() : pool.pop();
 vehicleInterpolationData.copy(data);
 if (this->buffer.empty()) {
 this->interpolationDataCurrentAdd(vehicle);
 }

 this->buffer.add(vehicleInterpolationData);
 this->update(GameTime.getServerTimeMills());
 }

 void interpolationDataAdd(ByteBuffer bb, long time, float x, float y, float z,
 long currentTime) {
 VehicleInterpolationData vehicleInterpolationData =
 pool.empty() ? new VehicleInterpolationData() : pool.pop();
 vehicleInterpolationData.time = time;
 vehicleInterpolationData.x = x;
 vehicleInterpolationData.y = y;
 vehicleInterpolationData.z = z;
 vehicleInterpolationData.qx = bb.getFloat();
 vehicleInterpolationData.qy = bb.getFloat();
 vehicleInterpolationData.qz = bb.getFloat();
 vehicleInterpolationData.qw = bb.getFloat();
 vehicleInterpolationData.vx = bb.getFloat();
 vehicleInterpolationData.vy = bb.getFloat();
 vehicleInterpolationData.vz = bb.getFloat();
 vehicleInterpolationData.engineSpeed = bb.getFloat();
 vehicleInterpolationData.throttle = bb.getFloat();
 vehicleInterpolationData.setNumWheels(bb.getShort());

 for (int int0 = 0; int0 < vehicleInterpolationData.wheelsCount; int0++) {
 vehicleInterpolationData.wheelSteering[int0] = bb.getFloat();
 vehicleInterpolationData.wheelRotation[int0] = bb.getFloat();
 vehicleInterpolationData.wheelSkidInfo[int0] = bb.getFloat();
 vehicleInterpolationData.wheelSuspensionLength[int0] = bb.getFloat();
 }

 this->buffer.add(vehicleInterpolationData);
 this->update(currentTime);
 }

 bool interpolationDataGet(float[] floats0, float[] floats1) {
 long long0 = WorldSimulation.instance.time - this->delay;
 return this->interpolationDataGet(floats0, floats1, long0);
 }

 bool interpolationDataGet(float[] floats1, float[] floats0, long long0) {
 temp.time = long0;
 VehicleInterpolationData vehicleInterpolationData0 =
 this->buffer.higher(temp);
 VehicleInterpolationData vehicleInterpolationData1 =
 this->buffer.floor(temp);
 if (this->buffering) {
 if (this->buffer.size() < 2 || vehicleInterpolationData0.empty() ||
 vehicleInterpolationData1.empty()) {
 return false;
 }

 this->buffering = false;
 } else if (this->buffer.empty()) {
 this->reset();
 return false;
 }

 int int0 = 0;
 if (vehicleInterpolationData0.empty()) {
 if (vehicleInterpolationData1.empty()) {
 this->reset();
 return false;
 } else {
 floats0[0] = vehicleInterpolationData1.engineSpeed;
 floats0[1] = vehicleInterpolationData1.throttle;
 floats1[int0++] = vehicleInterpolationData1.x;
 floats1[int0++] = vehicleInterpolationData1.y;
 floats1[int0++] = vehicleInterpolationData1.z;
 floats1[int0++] = vehicleInterpolationData1.qx;
 floats1[int0++] = vehicleInterpolationData1.qy;
 floats1[int0++] = vehicleInterpolationData1.qz;
 floats1[int0++] = vehicleInterpolationData1.qw;
 floats1[int0++] = vehicleInterpolationData1.vx;
 floats1[int0++] = vehicleInterpolationData1.vy;
 floats1[int0++] = vehicleInterpolationData1.vz;
 floats1[int0++] = vehicleInterpolationData1.wheelsCount;

 for (int int1 = 0; int1 < vehicleInterpolationData1.wheelsCount;
 int1++) {
 floats1[int0++] = vehicleInterpolationData1.wheelSteering[int1];
 floats1[int0++] = vehicleInterpolationData1.wheelRotation[int1];
 floats1[int0++] = vehicleInterpolationData1.wheelSkidInfo[int1];
 floats1[int0++] =
 vehicleInterpolationData1.wheelSuspensionLength[int1];
 }

 this->reset();
 return true;
 }
 } else if (vehicleInterpolationData1 != nullptr &&
 Math.abs(vehicleInterpolationData0.time -
 vehicleInterpolationData1.time) >= 10L) {
 float float0 = (float)(long0 - vehicleInterpolationData1.time) /
 (float)(vehicleInterpolationData0.time -
 vehicleInterpolationData1.time);
 floats0[0] = (vehicleInterpolationData0.engineSpeed -
 vehicleInterpolationData1.engineSpeed) *
 float0 +
 vehicleInterpolationData1.engineSpeed;
 floats0[1] = (vehicleInterpolationData0.throttle -
 vehicleInterpolationData1.throttle) *
 float0 +
 vehicleInterpolationData1.throttle;
 floats1[int0++] =
 (vehicleInterpolationData0.x - vehicleInterpolationData1.x) * float0 +
 vehicleInterpolationData1.x;
 floats1[int0++] =
 (vehicleInterpolationData0.y - vehicleInterpolationData1.y) * float0 +
 vehicleInterpolationData1.y;
 floats1[int0++] =
 (vehicleInterpolationData0.z - vehicleInterpolationData1.z) * float0 +
 vehicleInterpolationData1.z;
 tempQuaternionA.set(
 vehicleInterpolationData1.qx, vehicleInterpolationData1.qy,
 vehicleInterpolationData1.qz, vehicleInterpolationData1.qw);
 tempQuaternionB.set(
 vehicleInterpolationData0.qx, vehicleInterpolationData0.qy,
 vehicleInterpolationData0.qz, vehicleInterpolationData0.qw);
 tempQuaternionA.nlerp(tempQuaternionB, float0);
 floats1[int0++] = tempQuaternionA.x;
 floats1[int0++] = tempQuaternionA.y;
 floats1[int0++] = tempQuaternionA.z;
 floats1[int0++] = tempQuaternionA.w;
 floats1[int0++] =
 (vehicleInterpolationData0.vx - vehicleInterpolationData1.vx) *
 float0 +
 vehicleInterpolationData1.vx;
 floats1[int0++] =
 (vehicleInterpolationData0.vy - vehicleInterpolationData1.vy) *
 float0 +
 vehicleInterpolationData1.vy;
 floats1[int0++] =
 (vehicleInterpolationData0.vz - vehicleInterpolationData1.vz) *
 float0 +
 vehicleInterpolationData1.vz;
 floats1[int0++] = vehicleInterpolationData0.wheelsCount;

 for (int int2 = 0; int2 < vehicleInterpolationData0.wheelsCount; int2++) {
 floats1[int0++] = (vehicleInterpolationData0.wheelSteering[int2] -
 vehicleInterpolationData1.wheelSteering[int2]) *
 float0 +
 vehicleInterpolationData1.wheelSteering[int2];
 floats1[int0++] = (vehicleInterpolationData0.wheelRotation[int2] -
 vehicleInterpolationData1.wheelRotation[int2]) *
 float0 +
 vehicleInterpolationData1.wheelRotation[int2];
 floats1[int0++] = (vehicleInterpolationData0.wheelSkidInfo[int2] -
 vehicleInterpolationData1.wheelSkidInfo[int2]) *
 float0 +
 vehicleInterpolationData1.wheelSkidInfo[int2];
 floats1[int0++] =
 (vehicleInterpolationData0.wheelSuspensionLength[int2] -
 vehicleInterpolationData1.wheelSuspensionLength[int2]) *
 float0 +
 vehicleInterpolationData1.wheelSuspensionLength[int2];
 }

 return true;
 } else {
 return false;
 }
 }
}
} // namespace vehicles
} // namespace zombie
