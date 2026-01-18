#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LocationRNG {
public:
 static const LocationRNG instance = new LocationRNG();
 static const float INT_TO_FLOAT = Float.intBitsToFloat(864026624);
 long _s0;
 long _s1;
 long state;

 void setSeed(long long0) {
 this->state = long0;
 this->_s0 = this->nextSplitMix64();
 this->_s1 = this->nextSplitMix64();
 }

 long getSeed() { return this->state; }

 long nextSplitMix64() {
 long long0 = this->state += -7046029254386353131L;
 long0 = (long0 ^ long0 >>> 30) * -4658895280553007687L;
 long0 = (long0 ^ long0 >>> 27) * -7723592293110705685L;
 return long0 ^ long0 >>> 31;
 }

 float nextFloat() { return (this->nextInt() >>> 8) * INT_TO_FLOAT; }

 int nextInt() {
 long long0 = this->_s0;
 long long1 = this->_s1;
 long long2 = long0 + long1;
 long1 ^= long0;
 this->_s0 = Long.rotateLeft(long0, 55) ^ long1 ^ long1 << 14;
 this->_s1 = Long.rotateLeft(long1, 36);
 return (int)(long2 & -1L);
 }

 int nextInt(int int0) {
 long long0 = this->nextInt() >>> 1;
 long0 = long0 * int0 >> 31;
 return (int)long0;
 }

 int nextInt(int int3, int int0, int int1, int int2) {
 this->setSeed((long)int2 << 16 | (long)int1 << 32 | int0);
 return this->nextInt(int3);
 }
}
} // namespace util
} // namespace zombie
