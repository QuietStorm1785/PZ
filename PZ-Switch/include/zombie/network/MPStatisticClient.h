#pragma once
#include <mutex>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/iso/IsoUtils.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MPStatisticClient {
public:

 // Mutexes for synchronized blocks
 std::mutex fpsArray_mutex;
 static MPStatisticClient instance = new MPStatisticClient();
 bool needUpdate = true;
 int zombiesLocalOwnership = 0;
 float zombiesDesyncAVG = 0.0F;
 float zombiesDesyncMax = 0.0F;
 int zombiesTeleports = 0;
 float remotePlayersDesyncAVG = 0.0F;
 float remotePlayersDesyncMax = 0.0F;
 int remotePlayersTeleports = 0;
 float FPS = 0.0F;
 long lastRender = System.currentTimeMillis();
 short FPSAcc = 0;
private
 float[] fpsArray = new float[1000];
 short fpsArrayCount = 0;

 static MPStatisticClient getInstance() { return instance; }

 void incrementZombiesTeleports() { this->zombiesTeleports++; }

 void incrementRemotePlayersTeleports() { this->remotePlayersTeleports++; }

 float getFPS() { return this->FPS; }

 void update() {
 if (this->needUpdate) {
 this->needUpdate = false;

 for (int int0 = 0; int0 < GameClient.IDToZombieMap.values().length;
 int0++) {
 IsoZombie zombie0 = (IsoZombie)GameClient.IDToZombieMap.values()[int0];
 if (!zombie0.isRemoteZombie()) {
 this->zombiesLocalOwnership++;
 } else {
 float float0 =
 IsoUtils.DistanceTo(zombie0.x, zombie0.y, zombie0.z,
 zombie0.realx, zombie0.realy, zombie0.realz);
 this->zombiesDesyncAVG =
 this->zombiesDesyncAVG + (float0 - this->zombiesDesyncAVG) * 0.05F;
 if (float0 > this->zombiesDesyncMax) {
 this->zombiesDesyncMax = float0;
 }
 }
 }

 for (IsoPlayer player : GameClient.IDToPlayerMap.values()) {
 if (!player.isLocalPlayer()) {
 float float1 =
 IsoUtils.DistanceTo(player.x, player.y, player.z, player.realx,
 player.realy, player.realz);
 this->remotePlayersDesyncAVG =
 this->remotePlayersDesyncAVG +
 (float1 - this->remotePlayersDesyncAVG) * 0.05F;
 if (float1 > this->remotePlayersDesyncMax) {
 this->remotePlayersDesyncMax = float1;
 }
 }
 }
 }
 }

 void send(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putInt(GameClient.IDToZombieMap.size());
 byteBufferWriter.putInt(this->zombiesLocalOwnership);
 byteBufferWriter.putFloat(this->zombiesDesyncAVG);
 byteBufferWriter.putFloat(this->zombiesDesyncMax);
 byteBufferWriter.putInt(this->zombiesTeleports);
 byteBufferWriter.putInt(GameClient.IDToPlayerMap.size());
 byteBufferWriter.putFloat(this->remotePlayersDesyncAVG);
 byteBufferWriter.putFloat(this->remotePlayersDesyncMax);
 byteBufferWriter.putInt(this->remotePlayersTeleports);
 void *object = nullptr;
 short short0 = 0;
 { std::lock_guard<std::mutex> __sync_lock__(fpsArray_mutex);
 object = (float[])this->fpsArray.clone();
 Arrays.fill(this->fpsArray, 0, this->fpsArrayCount, 0.0F);
 short0 = this->fpsArrayCount;
 this->fpsArrayCount = 0;
 }

 float float0 = (float)((Object[])object)[0];
 float float1 = (float)((Object[])object)[0];
 float float2 = (float)((Object[])object)[0];
 short[] shorts = new short[32];
 Arrays.fill(shorts, (short)0);

 for (int int0 = 1; int0 < short0; int0++) {
 float float3 = (float)((Object[])object)[int0];
 if (float0 > float3) {
 float0 = float3;
 }

 if (float2 < float3) {
 float2 = float3;
 }

 float1 += float3;
 }

 float1 /= short0;
 if (float1 < float0 + 16.0F) {
 float0 = float1 - 16.0F;
 }

 if (float2 < float1 + 16.0F) {
 float2 = float1 + 16.0F;
 }

 float float4 = (float1 - float0) / (shorts.length / 2);
 float float5 = (float2 - float1) / (shorts.length / 2);

 for (int int1 = 0; int1 < short0; int1++) {
 float float6 = (float)((Object[])object)[int1];
 if (float6 < float1) {
 int int2 = (int)Math.ceil((float6 - float0) / float4);
 shorts[int2]++;
 }

 if (float6 >= float1) {
 int int3 =
 (int)Math.ceil((float6 - float1) / float5) + shorts.length / 2 - 1;
 shorts[int3]++;
 }
 }

 byteBufferWriter.putFloat(this->FPS);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);

 for (int int4 = 0; int4 < shorts.length; int4++) {
 byteBufferWriter.putShort(shorts[int4]);
 }

 this->zombiesDesyncMax = 0.0F;
 this->zombiesTeleports = 0;
 this->remotePlayersDesyncMax = 0.0F;
 this->remotePlayersTeleports = 0;
 this->zombiesLocalOwnership = 0;
 this->needUpdate = true;
 }

 void fpsProcess() {
 this->FPSAcc++;
 long long0 = System.currentTimeMillis();
 if (long0 - this->lastRender >= 1000L) {
 this->FPS = this->FPSAcc;
 this->FPSAcc = 0;
 this->lastRender = long0;
 if (this->fpsArrayCount < this->fpsArray.length) {
 { std::lock_guard<std::mutex> __sync_lock__(fpsArray_mutex);
 this->fpsArray[this->fpsArrayCount] = this->FPS;
 this->fpsArrayCount++;
 }
 }
 }
 }
}
} // namespace network
} // namespace zombie
