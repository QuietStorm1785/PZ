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


class Murmur3_128HashFunction {
public:
    static const int CHUNK_SIZE = 16;
    static const long C1 = -8663945395140668459L;
    static const long C2 = 5545529020109919103L;
    long h1;
    long h2;
    int length;

   Murmur3_128HashFunction$Murmur3_128Hasher(int seed) {
      super(16);
      this.h1 = seed;
      this.h2 = seed;
      this.length = 0;
   }

    void process(ByteBuffer bb) {
    long k1 = bb.getLong();
    long k2 = bb.getLong();
      this.bmix64(k1, k2);
      this.length += 16;
   }

    void bmix64(long k1, long k2) {
      this.h1 = this.h1 ^ mixK1(k1);
      this.h1 = int64_t.rotateLeft(this.h1, 27);
      this.h1 = this.h1 + this.h2;
      this.h1 = this.h1 * 5L + 1390208809L;
      this.h2 = this.h2 ^ mixK2(k2);
      this.h2 = int64_t.rotateLeft(this.h2, 31);
      this.h2 = this.h2 + this.h1;
      this.h2 = this.h2 * 5L + 944331445L;
   }

    void processRemaining(ByteBuffer bb) {
    long k1 = 0L;
    long k2 = 0L;
      this.length = this.length + bb.remaining();
      switch (bb.remaining()) {
         case 7:
            k1 ^= (long)UnsignedBytes.toInt(bb.get(6)) << 48;
         case 6:
            k1 ^= (long)UnsignedBytes.toInt(bb.get(5)) << 40;
         case 5:
            k1 ^= (long)UnsignedBytes.toInt(bb.get(4)) << 32;
         case 4:
            k1 ^= (long)UnsignedBytes.toInt(bb.get(3)) << 24;
         case 3:
            k1 ^= (long)UnsignedBytes.toInt(bb.get(2)) << 16;
         case 2:
            k1 ^= (long)UnsignedBytes.toInt(bb.get(1)) << 8;
         case 1:
            k1 ^= UnsignedBytes.toInt(bb.get(0));
            break;
         case 15:
            k2 ^= (long)UnsignedBytes.toInt(bb.get(14)) << 48;
         case 14:
            k2 ^= (long)UnsignedBytes.toInt(bb.get(13)) << 40;
         case 13:
            k2 ^= (long)UnsignedBytes.toInt(bb.get(12)) << 32;
         case 12:
            k2 ^= (long)UnsignedBytes.toInt(bb.get(11)) << 24;
         case 11:
            k2 ^= (long)UnsignedBytes.toInt(bb.get(10)) << 16;
         case 10:
            k2 ^= (long)UnsignedBytes.toInt(bb.get(9)) << 8;
         case 9:
            k2 ^= UnsignedBytes.toInt(bb.get(8));
         case 8:
            k1 ^= bb.getLong();
            break;
         default:
            throw AssertionError("Should never get here.");
      }

      this.h1 = this.h1 ^ mixK1(k1);
      this.h2 = this.h2 ^ mixK2(k2);
   }

    HashCode makeHash() {
      this.h1 = this.h1 ^ this.length;
      this.h2 = this.h2 ^ this.length;
      this.h1 = this.h1 + this.h2;
      this.h2 = this.h2 + this.h1;
      this.h1 = fmix64(this.h1);
      this.h2 = fmix64(this.h2);
      this.h1 = this.h1 + this.h2;
      this.h2 = this.h2 + this.h1;
      return HashCode.fromBytesNoCopy(ByteBuffer.wrap(new byte[16]).order(ByteOrder.LITTLE_ENDIAN).putLong(this.h1).putLong(this.h2).array());
   }

    static long fmix64(long k) {
      k ^= k >>> 33;
      k *= -49064778989728563L;
      k ^= k >>> 33;
      k *= -4265267296055464877L;
      return k ^ k >>> 33;
   }

    static long mixK1(long k1) {
      k1 *= -8663945395140668459L;
      k1 = int64_t.rotateLeft(k1, 31);
      return k1 * 5545529020109919103L;
   }

    static long mixK2(long k2) {
      k2 *= 5545529020109919103L;
      k2 = int64_t.rotateLeft(k2, 33);
      return k2 * -8663945395140668459L;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
