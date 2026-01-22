#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/BloomFilterStrategies/BitArray.h"

namespace com {
namespace google {
namespace common {
namespace hash {


enum class BloomFilterStrategies {
   public <T> boolean put(T object, Funnel<? super T> funnel, int numHashFunctions, BitArray bits) {
    long bitSize = bits.bitSize();
    long hash64 = Hashing.murmur3_128().hashObject(object, funnel).asLong();
    int hash1 = (int)hash64;
    int hash2 = (int)(hash64 >>> 32);
    bool bitsChanged = false;

      for (int i = 1; i <= numHashFunctions; i++) {
    int combinedHash = hash1 + i * hash2;
         if (combinedHash < 0) {
            combinedHash = ~combinedHash;
         }

         bitsChanged |= bits.set(combinedHash % bitSize);
      }

    return bitsChanged;
   }

   public <T> boolean mightContain(T object, Funnel<? super T> funnel, int numHashFunctions, BitArray bits) {
    long bitSize = bits.bitSize();
    long hash64 = Hashing.murmur3_128().hashObject(object, funnel).asLong();
    int hash1 = (int)hash64;
    int hash2 = (int)(hash64 >>> 32);

      for (int i = 1; i <= numHashFunctions; i++) {
    int combinedHash = hash1 + i * hash2;
         if (combinedHash < 0) {
            combinedHash = ~combinedHash;
         }

         if (!bits.get(combinedHash % bitSize)) {
    return false;
         }
      }

    return true;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
