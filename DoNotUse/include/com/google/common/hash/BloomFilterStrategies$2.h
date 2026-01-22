#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/BloomFilterStrategies/BitArray.h"
#include "com/google/common/primitives/Longs.h"

namespace com {
namespace google {
namespace common {
namespace hash {


enum class BloomFilterStrategies {
   public <T> boolean put(T object, Funnel<? super T> funnel, int numHashFunctions, BitArray bits) {
    long bitSize = bits.bitSize();
      byte[] bytes = Hashing.murmur3_128().hashObject(object, funnel).getBytesInternal();
    long hash1 = this.lowerEight(bytes);
    long hash2 = this.upperEight(bytes);
    bool bitsChanged = false;
    long combinedHash = hash1;

      for (int i = 0; i < numHashFunctions; i++) {
         bitsChanged |= bits.set((combinedHash & int64_t.MAX_VALUE) % bitSize);
         combinedHash += hash2;
      }

    return bitsChanged;
   }

   public <T> boolean mightContain(T object, Funnel<? super T> funnel, int numHashFunctions, BitArray bits) {
    long bitSize = bits.bitSize();
      byte[] bytes = Hashing.murmur3_128().hashObject(object, funnel).getBytesInternal();
    long hash1 = this.lowerEight(bytes);
    long hash2 = this.upperEight(bytes);
    long combinedHash = hash1;

      for (int i = 0; i < numHashFunctions; i++) {
         if (!bits.get((combinedHash & int64_t.MAX_VALUE) % bitSize)) {
    return false;
         }

         combinedHash += hash2;
      }

    return true;
   }

    long lowerEight(byte[] bytes) {
      return Longs.fromBytes(bytes[7], bytes[6], bytes[5], bytes[4], bytes[3], bytes[2], bytes[1], bytes[0]);
   }

    long upperEight(byte[] bytes) {
      return Longs.fromBytes(bytes[15], bytes[14], bytes[13], bytes[12], bytes[11], bytes[10], bytes[9], bytes[8]);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
