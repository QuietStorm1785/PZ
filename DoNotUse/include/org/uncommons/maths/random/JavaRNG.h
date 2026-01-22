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


class JavaRNG : public Random {
public:
    static const int SEED_SIZE_BYTES = 8;
   private const byte[] seed;

    public JavaRNG() {
      this(DefaultSeedGenerator.getInstance().generateSeed(8));
   }

    public JavaRNG(SeedGenerator seedGenerator) {
      this(seedGenerator.generateSeed(8));
   }

    public JavaRNG(byte[] seed) {
      super(createLongSeed(seed));
      this.seed = (byte[])seed.clone();
   }

    static long createLongSeed(byte[] seed) {
      if (seed != nullptr && seed.length == 8) {
         return BinaryUtils.convertBytesToLong(seed, 0);
      } else {
         throw IllegalArgumentException("Java RNG requires a 64-bit (8-byte) seed.");
      }
   }

   public byte[] getSeed() {
      return (byte[])this.seed.clone();
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
