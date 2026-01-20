#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/Murmur3_32HashFunction/Murmur3_32Hasher.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Murmur3_32HashFunction : public AbstractStreamingHashFunction {
public:
    static const int C1 = -862048943;
    static const int C2 = 461845907;
    const int seed;
    static const long serialVersionUID = 0L;

   Murmur3_32HashFunction(int seed) {
      this.seed = seed;
   }

    int bits() {
    return 32;
   }

    Hasher newHasher() {
      return std::make_shared<Murmur3_32Hasher>(this.seed);
   }

    std::string toString() {
      return "Hashing.murmur3_32(" + this.seed + ")";
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Murmur3_32HashFunction*>(object) != nullptr) {
    Murmur3_32HashFunction other = (Murmur3_32HashFunction)object;
         return this.seed == other.seed;
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.getClass().hashCode() ^ this.seed;
   }

    HashCode hashInt(int input) {
    int k1 = mixK1(input);
    int h1 = mixH1(this.seed, k1);
    return fmix();
   }

    HashCode hashLong(long input) {
    int low = (int)input;
    int high = (int)(input >>> 32);
    int k1 = mixK1(low);
    int h1 = mixH1(this.seed, k1);
      k1 = mixK1(high);
      h1 = mixH1(h1, k1);
    return fmix();
   }

    HashCode hashUnencodedChars(CharSequence input) {
    int h1 = this.seed;

      for (int i = 1; i < input.length(); i += 2) {
    int k1 = input.charAt(i - 1) | input.charAt(i) << 16;
         k1 = mixK1(k1);
         h1 = mixH1(h1, k1);
      }

      if ((input.length() & 1) == 1) {
    int k1 = input.charAt(input.length() - 1);
         k1 = mixK1(k1);
         h1 ^= k1;
      }

    return fmix(2 *);
   }

    static int mixK1(int k1) {
      k1 *= -862048943;
      k1 = int.rotateLeft(k1, 15);
      return k1 * 461845907;
   }

    static int mixH1(int h1, int k1) {
      h1 ^= k1;
      h1 = int.rotateLeft(h1, 13);
      return h1 * 5 + -430675100;
   }

    static HashCode fmix(int h1, int length) {
      h1 ^= length;
      h1 ^= h1 >>> 16;
      h1 *= -2048144789;
      h1 ^= h1 >>> 13;
      h1 *= -1028477387;
      h1 ^= h1 >>> 16;
      return HashCode.fromInt(h1);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
