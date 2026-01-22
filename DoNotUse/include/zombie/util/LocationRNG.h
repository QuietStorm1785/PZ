#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class LocationRNG {
public:
    static const LocationRNG instance = std::make_shared<LocationRNG>();
    static const float INT_TO_FLOAT = float.intBitsToFloat(864026624);
    long _s0;
    long _s1;
    long state;

    void setSeed(long var1) {
      this.state = var1;
      this._s0 = this.nextSplitMix64();
      this._s1 = this.nextSplitMix64();
   }

    long getSeed() {
      return this.state;
   }

    long nextSplitMix64() {
    long var1 = this.state += -7046029254386353131L;
      var1 = (var1 ^ var1 >>> 30) * -4658895280553007687L;
      var1 = (var1 ^ var1 >>> 27) * -7723592293110705685L;
      return var1 ^ var1 >>> 31;
   }

    float nextFloat() {
      return (this.nextInt() >>> 8) * INT_TO_FLOAT;
   }

    int nextInt() {
    long var1 = this._s0;
    long var3 = this._s1;
    long var5 = var1 + var3;
      var3 ^= var1;
      this._s0 = int64_t.rotateLeft(var1, 55) ^ var3 ^ var3 << 14;
      this._s1 = int64_t.rotateLeft(var3, 36);
      return (int)(var5 & -1L);
   }

    int nextInt(int var1) {
    long var2 = this.nextInt() >>> 1;
      var2 = var2 * var1 >> 31;
      return (int)var2;
   }

    int nextInt(int var1, int var2, int var3, int var4) {
      this.setSeed((long)var4 << 16 | (long)var3 << 32 | var2);
      return this.nextInt(var1);
   }
}
} // namespace util
} // namespace zombie
