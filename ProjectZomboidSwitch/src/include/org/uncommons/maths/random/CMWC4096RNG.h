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


class CMWC4096RNG : public Random {
public:
    static const int SEED_SIZE_BYTES = 16384;
    static const long A = 18782L;
   private const byte[] seed;
   private const int[] state;
    int carry = 362436;
    int index = 4095;
    const ReentrantLock lock = std::make_shared<ReentrantLock>();

    public CMWC4096RNG() {
      this(DefaultSeedGenerator.getInstance().generateSeed(16384));
   }

    public CMWC4096RNG(SeedGenerator seedGenerator) {
      this(seedGenerator.generateSeed(16384));
   }

    public CMWC4096RNG(byte[] seed) {
      if (seed != nullptr && seed.length == 16384) {
         this.seed = (byte[])seed.clone();
         this.state = BinaryUtils.convertBytesToInts(seed);
      } else {
         throw IllegalArgumentException("CMWC RNG requires 16kb of seed data.");
      }
   }

   public byte[] getSeed() {
      return (byte[])this.seed.clone();
   }

    int next(int bits) {
    int var5;
      try {
         this.lock.lock();
         this.index = this.index + 1 & 4095;
    long t = 18782L * (this.state[this.index] & 4294967295L) + this.carry;
         this.carry = (int)(t >> 32);
    int x = (int)t + this.carry;
         if (x < this.carry) {
            x++;
            this.carry++;
         }

         this.state[this.index] = -2 - x;
         var5 = this.state[this.index] >>> 32 - bits;
      } finally {
         this.lock.unlock();
      }

    return var5;
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
