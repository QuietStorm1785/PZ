#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/AbstractStreamingHashFunction/AbstractStreamingHasher.h"
#include "com/google/common/primitives/UnsignedBytes.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class Murmur3_32HashFunction {
public:
    static const int CHUNK_SIZE = 4;
    int h1;
    int length;

   Murmur3_32HashFunction$Murmur3_32Hasher(int seed) {
      super(4);
      this.h1 = seed;
      this.length = 0;
   }

    void process(ByteBuffer bb) {
    int k1 = Murmur3_32HashFunction.access$000(bb.getInt());
      this.h1 = Murmur3_32HashFunction.access$100(this.h1, k1);
      this.length += 4;
   }

    void processRemaining(ByteBuffer bb) {
      this.length = this.length + bb.remaining();
    int k1 = 0;

      for (int i = 0; bb.hasRemaining(); i += 8) {
         k1 ^= UnsignedBytes.toInt(bb.get()) << i;
      }

      this.h1 = this.h1 ^ Murmur3_32HashFunction.access$000(k1);
   }

    HashCode makeHash() {
      return Murmur3_32HashFunction.access$200(this.h1, this.length);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
