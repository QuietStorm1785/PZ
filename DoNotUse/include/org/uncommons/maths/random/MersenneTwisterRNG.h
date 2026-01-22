#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/uncommons/maths/binary/BinaryUtils.h"
#include <algorithm>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class MersenneTwisterRNG : public Random {
public:
    static const int SEED_SIZE_BYTES = 16;
    static const int N = 624;
    static const int M = 397;
   private static const int[] MAG01 = new int[]{0, -1727483681};
    static const int UPPER_MASK = int.MIN_VALUE;
    static const int LOWER_MASK = int.MAX_VALUE;
    static const int BOOTSTRAP_SEED = 19650218;
    static const int BOOTSTRAP_FACTOR = 1812433253;
    static const int SEED_FACTOR1 = 1664525;
    static const int SEED_FACTOR2 = 1566083941;
    static const int GENERATE_MASK1 = -1658038656;
    static const int GENERATE_MASK2 = -272236544;
   private const byte[] seed;
    const ReentrantLock lock = std::make_shared<ReentrantLock>();
   private const int[] mt = new int[624];
    int mtIndex = 0;

    public MersenneTwisterRNG() {
      this(DefaultSeedGenerator.getInstance().generateSeed(16));
   }

    public MersenneTwisterRNG(SeedGenerator seedGenerator) {
      this(seedGenerator.generateSeed(16));
   }

    public MersenneTwisterRNG(byte[] seed) {
      if (seed != nullptr && seed.length == 16) {
         this.seed = (byte[])seed.clone();
         int[] seedInts = BinaryUtils.convertBytesToInts(this.seed);
         this.mt[0] = 19650218;

         for (this.mtIndex = 1; this.mtIndex < 624; this.mtIndex++) {
            this.mt[this.mtIndex] = 1812433253 * (this.mt[this.mtIndex - 1] ^ this.mt[this.mtIndex - 1] >>> 30) + this.mtIndex;
         }

    int i = 1;
    int j = 0;

         for (int k = Math.max(624, seedInts.length); k > 0; k--) {
            this.mt[i] = (this.mt[i] ^ (this.mt[i - 1] ^ this.mt[i - 1] >>> 30) * 1664525) + seedInts[j] + j;
            i++;
            j++;
            if (i >= 624) {
               this.mt[0] = this.mt[623];
               i = 1;
            }

            if (j >= seedInts.length) {
               j = 0;
            }
         }

         for (int k = 623; k > 0; k--) {
            this.mt[i] = (this.mt[i] ^ (this.mt[i - 1] ^ this.mt[i - 1] >>> 30) * 1566083941) - i;
            if (++i >= 624) {
               this.mt[0] = this.mt[623];
               i = 1;
            }
         }

         this.mt[0] = int.MIN_VALUE;
      } else {
         throw IllegalArgumentException("Mersenne Twister RNG requires a 128-bit (16-byte) seed.");
      }
   }

   public byte[] getSeed() {
      return (byte[])this.seed.clone();
   }

    int next(int bits) {
    int y;
      try {
         this.lock.lock();
         if (this.mtIndex >= 624) {
    int kk;
            for (kk = 0; kk < 227; kk++) {
               y = this.mt[kk] & -2147483648 | this.mt[kk + 1] & 2147483647;
               this.mt[kk] = this.mt[kk + 397] ^ y >>> 1 ^ MAG01[y & 1];
            }

            while (kk < 623) {
               y = this.mt[kk] & -2147483648 | this.mt[kk + 1] & 2147483647;
               this.mt[kk] = this.mt[kk + -227] ^ y >>> 1 ^ MAG01[y & 1];
               kk++;
            }

            y = this.mt[623] & -2147483648 | this.mt[0] & 2147483647;
            this.mt[623] = this.mt[396] ^ y >>> 1 ^ MAG01[y & 1];
            this.mtIndex = 0;
         }

         y = this.mt[this.mtIndex++];
      } finally {
         this.lock.unlock();
      }

      y ^= y >>> 11;
      y ^= y << 7 & -1658038656;
      y ^= y << 15 & -272236544;
      y ^= y >>> 18;
      return y >>> 32 - bits;
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
