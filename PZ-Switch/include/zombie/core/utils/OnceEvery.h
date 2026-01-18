#pragma once
#include "zombie/GameTime.h"
#include "zombie/core/Rand.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class OnceEvery {
public:
 long initialDelayMillis = 0L;
 long triggerIntervalMillis;
 static float milliFraction = 0.0F;
 static long currentMillis = 0L;
 static long prevMillis = 0L;

public
 OnceEvery(float seconds) { this(seconds, false); }

public
 OnceEvery(float seconds, bool randomStart) {
 this->triggerIntervalMillis = (long)(seconds * 1000.0F);
 this->initialDelayMillis = 0L;
 if (randomStart) {
 this->initialDelayMillis = Rand.Next(this->triggerIntervalMillis);
 }
 }

 static long getElapsedMillis() { return currentMillis; }

 bool Check() {
 if (currentMillis < this->initialDelayMillis) {
 return false;
 } else if (this->triggerIntervalMillis == 0L) {
 return true;
 } else {
 long long0 =
 (prevMillis - this->initialDelayMillis) % this->triggerIntervalMillis;
 long long1 = (currentMillis - this->initialDelayMillis) %
 this->triggerIntervalMillis;
 if (long0 > long1) {
 return true;
 } else {
 long long2 = currentMillis - prevMillis;
 return this->triggerIntervalMillis < long2;
 }
 }
 }

 static void update() {
 long long0 = currentMillis;
 float float0 = milliFraction;
 float float1 = GameTime.instance.getTimeDelta();
 float float2 = float1 * 1000.0F + float0;
 long long1 = (long)float2;
 float float3 = float2 - (float)long1;
 long long2 = long0 + long1;
 prevMillis = long0;
 currentMillis = long2;
 milliFraction = float3;
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
