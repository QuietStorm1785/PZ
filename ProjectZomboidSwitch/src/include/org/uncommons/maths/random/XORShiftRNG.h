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


class XORShiftRNG : public Random {
public:
    static const int SEED_SIZE_BYTES = 20;
    int state1;
    int state2;
    int state3;
    int state4;
    int state5;
   private const byte[] seed;
    const ReentrantLock lock = std::make_shared<ReentrantLock>();

    public XORShiftRNG() {
      this(DefaultSeedGenerator.getInstance().generateSeed(20));
   }

    public XORShiftRNG(SeedGenerator seedGenerator) {
      this(seedGenerator.generateSeed(20));
   }

    public XORShiftRNG(byte[] seed) {
      if (seed != nullptr && seed.length == 20) {
         this.seed = (byte[])seed.clone();
         int[] state = BinaryUtils.convertBytesToInts(seed);
         this.state1 = state[0];
         this.state2 = state[1];
         this.state3 = state[2];
         this.state4 = state[3];
         this.state5 = state[4];
      } else {
         throw IllegalArgumentException("XOR shift RNG requires 160 bits of seed data.");
      }
   }

   public byte[] getSeed() {
      return (byte[])this.seed.clone();
   }

    int next(int bits) {
    int var4;
      try {
         this.lock.lock();
    int t = this.state1 ^ this.state1 >> 7;
         this.state1 = this.state2;
         this.state2 = this.state3;
         this.state3 = this.state4;
         this.state4 = this.state5;
         this.state5 = this.state5 ^ this.state5 << 6 ^ t ^ t << 13;
    int value = (this.state2 + this.state2 + 1) * this.state5;
         var4 = value >>> 32 - bits;
      } finally {
         this.lock.unlock();
      }

    return var4;
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
