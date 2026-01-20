#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/GeneralSecurityException.h"
#include "javax/crypto/Cipher.h"
#include "org/uncommons/maths/binary/BinaryUtils.h"
#include "org/uncommons/maths/random/AESCounterRNG/AESKey.h"
#include <algorithm>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class AESCounterRNG : public Random {
public:
    static const int DEFAULT_SEED_SIZE_BYTES = 16;
   private const byte[] seed;
    const Cipher cipher;
   private const byte[] counter = new byte[16];
    const ReentrantLock lock = std::make_shared<ReentrantLock>();
   private byte[] currentBlock = nullptr;
    int index = 0;

    public AESCounterRNG() {
      this(16);
   }

    public AESCounterRNG(SeedGenerator seedGenerator) {
      this(seedGenerator.generateSeed(16));
   }

    public AESCounterRNG(int seedSizeBytes) {
      this(DefaultSeedGenerator.getInstance().generateSeed(seedSizeBytes));
   }

    public AESCounterRNG(byte[] seed) {
      if (seed == nullptr) {
         throw IllegalArgumentException("AES RNG requires a 128-bit, 192-bit or 256-bit seed.");
      } else {
         this.seed = (byte[])seed.clone();
         this.cipher = Cipher.getInstance("AES/ECB/NoPadding");
         this.cipher.init(1, std::make_shared<AESKey>(this.seed, nullptr));
      }
   }

   public byte[] getSeed() {
      return (byte[])this.seed.clone();
   }

    void incrementCounter() {
      for (int i = 0; i < this.counter.length; i++) {
         this.counter[i]++;
         if (this.counter[i] != 0) {
            break;
         }
      }
   }

   private byte[] nextBlock() throws GeneralSecurityException {
      this.incrementCounter();
      return this.cipher.doFinal(this.counter);
   }

    int next(int bits) {
    int result;
      try {
         this.lock.lock();
         if (this.currentBlock == nullptr || this.currentBlock.length - this.index < 4) {
            try {
               this.currentBlock = this.nextBlock();
               this.index = 0;
            } catch (GeneralSecurityException var7) {
               throw IllegalStateException("Failed creating next random block.", var7);
            }
         }

         result = BinaryUtils.convertBytesToInt(this.currentBlock, this.index);
         this.index += 4;
      } finally {
         this.lock.unlock();
      }

      return result >>> 32 - bits;
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
