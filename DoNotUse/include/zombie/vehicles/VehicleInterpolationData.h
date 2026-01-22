#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

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
   protected float[] wheelSteering = new float[4];
   protected float[] wheelRotation = new float[4];
   protected float[] wheelSkidInfo = new float[4];
   protected float[] wheelSuspensionLength = new float[4];

    void setNumWheels(short var1) {
      if (var1 > this.wheelsCount) {
         this.wheelSteering = new float[var1];
         this.wheelRotation = new float[var1];
         this.wheelSkidInfo = new float[var1];
         this.wheelSuspensionLength = new float[var1];
      }

      this.wheelsCount = var1;
   }

    void copy(VehicleInterpolationData var1) {
      this.time = var1.time;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.qx = var1.qx;
      this.qy = var1.qy;
      this.qz = var1.qz;
      this.qw = var1.qw;
      this.vx = var1.vx;
      this.vy = var1.vy;
      this.vz = var1.vz;
      this.engineSpeed = var1.engineSpeed;
      this.throttle = var1.throttle;
      this.setNumWheels(var1.wheelsCount);

      for (int var2 = 0; var2 < var1.wheelsCount; var2++) {
         this.wheelSteering[var2] = var1.wheelSteering[var2];
         this.wheelRotation[var2] = var1.wheelRotation[var2];
         this.wheelSkidInfo[var2] = var1.wheelSkidInfo[var2];
         this.wheelSuspensionLength[var2] = var1.wheelSuspensionLength[var2];
      }
   }

    int compareTo(VehicleInterpolationData var1) {
      return int64_t.compare(this.time, var1.time);
   }
}
} // namespace vehicles
} // namespace zombie
