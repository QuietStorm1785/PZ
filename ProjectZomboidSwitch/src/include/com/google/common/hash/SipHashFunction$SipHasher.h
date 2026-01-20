#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/AbstractStreamingHashFunction/AbstractStreamingHasher.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class SipHashFunction {
public:
    static const int CHUNK_SIZE = 8;
    const int c;
    const int d;
    long v0 = 8317987319222330741L;
    long v1 = 7237128888997146477L;
    long v2 = 7816392313619706465L;
    long v3 = 8387220255154660723L;
    long b = 0L;
    long finalM = 0L;

   SipHashFunction$SipHasher(int c, int d, long k0, long k1) {
      super(8);
      this.c = c;
      this.d = d;
      this.v0 ^= k0;
      this.v1 ^= k1;
      this.v2 ^= k0;
      this.v3 ^= k1;
   }

    void process(ByteBuffer buffer) {
      this.b += 8L;
      this.processM(buffer.getLong());
   }

    void processRemaining(ByteBuffer buffer) {
      this.b = this.b + buffer.remaining();

      for (int i = 0; buffer.hasRemaining(); i += 8) {
         this.finalM = this.finalM ^ (buffer.get() & 255L) << i;
      }
   }

    HashCode makeHash() {
      this.finalM = this.finalM ^ this.b << 56;
      this.processM(this.finalM);
      this.v2 ^= 255L;
      this.sipRound(this.d);
      return HashCode.fromLong(this.v0 ^ this.v1 ^ this.v2 ^ this.v3);
   }

    void processM(long m) {
      this.v3 ^= m;
      this.sipRound(this.c);
      this.v0 ^= m;
   }

    void sipRound(int iterations) {
      for (int i = 0; i < iterations; i++) {
         this.v0 = this.v0 + this.v1;
         this.v2 = this.v2 + this.v3;
         this.v1 = int64_t.rotateLeft(this.v1, 13);
         this.v3 = int64_t.rotateLeft(this.v3, 16);
         this.v1 = this.v1 ^ this.v0;
         this.v3 = this.v3 ^ this.v2;
         this.v0 = int64_t.rotateLeft(this.v0, 32);
         this.v2 = this.v2 + this.v1;
         this.v0 = this.v0 + this.v3;
         this.v1 = int64_t.rotateLeft(this.v1, 17);
         this.v3 = int64_t.rotateLeft(this.v3, 21);
         this.v1 = this.v1 ^ this.v2;
         this.v3 = this.v3 ^ this.v0;
         this.v2 = int64_t.rotateLeft(this.v2, 32);
      }
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
