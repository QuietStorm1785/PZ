#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/primitives/UnsignedInts.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class HashCode {
public:
    const int hash;
    static const long serialVersionUID = 0L;

   HashCode$IntHashCode(int hash) {
      this.hash = hash;
   }

    int bits() {
    return 32;
   }

   public byte[] asBytes() {
      return new byte[]{(byte)this.hash, (byte)(this.hash >> 8), (byte)(this.hash >> 16), (byte)(this.hash >> 24)};
   }

    int asInt() {
      return this.hash;
   }

    long asLong() {
      throw IllegalStateException("this HashCode only has 32 bits; cannot create a long");
   }

    long padToLong() {
      return UnsignedInts.toLong(this.hash);
   }

    void writeBytesToImpl(byte[] dest, int offset, int maxLength) {
      for (int i = 0; i < maxLength; i++) {
         dest[offset + i] = (byte)(this.hash >> i * 8);
      }
   }

    bool equalsSameBits(HashCode that) {
      return this.hash == that.asInt();
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
