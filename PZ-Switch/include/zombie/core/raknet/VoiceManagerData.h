#pragma once
#include "zombie/radio/devices/DeviceData.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace raknet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VoiceManagerData {
public:
public
 static ArrayList<VoiceManagerData> data = std::make_unique<ArrayList<>>();
 long userplaychannel;
 long userplaysound;
 bool userplaymute;
 long voicetimeout;
public
 ArrayList<VoiceManagerData.RadioData> radioData =
 std::make_unique<ArrayList<>>();
 bool isCanHearAll;
 short index;

public
 VoiceManagerData(short short0) {
 this->userplaymute = false;
 this->userplaychannel = 0L;
 this->userplaysound = 0L;
 this->voicetimeout = 0L;
 this->index = short0;
 }

 static VoiceManagerData get(short short0) {
 if (data.size() <= short0) {
 for (short short1 = (short)data.size(); short1 <= short0; short1++) {
 VoiceManagerData voiceManagerData0 = new VoiceManagerData(short1);
 data.add(voiceManagerData0);
 }
 }

 VoiceManagerData voiceManagerData1 = data.get(short0);
 if (voiceManagerData1.empty()) {
 voiceManagerData1 = new VoiceManagerData(short0);
 data.set(short0, voiceManagerData1);
 }

 return voiceManagerData1;
 }

public
 static class RadioData {
 DeviceData deviceData;
 int freq;
 float distance;
 short x;
 short y;
 float lastReceiveDistance;

 public
 RadioData(float float0, float float1, float float2) {
 this(nullptr, 0, float0, float1, float2);
 }

 public
 RadioData(int int0, float float0, float float1, float float2) {
 this(nullptr, int0, float0, float1, float2);
 }

 public
 RadioData(DeviceData deviceDatax, float float0, float float1) {
 this(deviceDatax, deviceDatax.getChannel(),
 deviceDatax.getMicIsMuted() ? 0.0F : deviceDatax.getTransmitRange(),
 float0, float1);
 }

 private
 RadioData(DeviceData deviceDatax, int int0, float float0, float float1,
 float float2) {
 this->deviceData = deviceDatax;
 this->freq = int0;
 this->distance = float0;
 this->x = (short)float1;
 this->y = (short)float2;
 }

 bool isTransmissionAvailable() {
 return this->freq != 0 && this->deviceData != nullptr &&
 this->deviceData.getIsTurnedOn() && this->deviceData.getIsTwoWay() &&
 !this->deviceData.isNoTransmit() &&
 !this->deviceData.getMicIsMuted();
 }

 bool isReceivingAvailable(int int0) {
 return this->freq != 0 && this->deviceData != nullptr &&
 this->deviceData.getIsTurnedOn() &&
 this->deviceData.getChannel() == int0 &&
 this->deviceData.getDeviceVolume() != 0.0F &&
 !this->deviceData.isPlayingMedia();
 }

 DeviceData getDeviceData() { return this->deviceData; }
 }

 public static enum VoiceDataSource {
 Unknown, Voice, Radio, Cheat;
 }
}
} // namespace raknet
} // namespace core
} // namespace zombie
