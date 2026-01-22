#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/devices/DeviceData.h"

namespace zombie {
namespace core {
namespace raknet {


class VoiceManagerData {
public:
    DeviceData deviceData;
    int freq;
    float distance;
    short x;
    short y;
    float lastReceiveDistance;

   public VoiceManagerData$RadioData(float var1, float var2, float var3) {
      this(nullptr, 0, var1, var2, var3);
   }

   public VoiceManagerData$RadioData(int var1, float var2, float var3, float var4) {
      this(nullptr, var1, var2, var3, var4);
   }

   public VoiceManagerData$RadioData(DeviceData var1, float var2, float var3) {
      this(var1, var1.getChannel(), var1.getMicIsMuted() ? 0.0F : var1.getTransmitRange(), var2, var3);
   }

   private VoiceManagerData$RadioData(DeviceData var1, int var2, float var3, float var4, float var5) {
      this.deviceData = var1;
      this.freq = var2;
      this.distance = var3;
      this.x = (short)var4;
      this.y = (short)var5;
   }

    bool isTransmissionAvailable() {
      return this.freq != 0
         && this.deviceData != nullptr
         && this.deviceData.getIsTurnedOn()
         && this.deviceData.getIsTwoWay()
         && !this.deviceData.isNoTransmit()
         && !this.deviceData.getMicIsMuted();
   }

    bool isReceivingAvailable(int var1) {
      return this.freq != 0
         && this.deviceData != nullptr
         && this.deviceData.getIsTurnedOn()
         && this.deviceData.getChannel() == var1
         && this.deviceData.getDeviceVolume() != 0.0F
         && !this.deviceData.isPlayingMedia();
   }

    DeviceData getDeviceData() {
      return this.deviceData;
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
