#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class HashCode {
public:
    const long hash;
    static const long serialVersionUID = 0L;

   HashCode$LongHashCode(long hash) {
      this.hash = hash;
   }

    int bits() {
    return 64;
   }

   public byte[] asBytes() {
      return new byte[]{
         (byte)this.hash,
         (byte)(this.hash >> 8),
         (byte)(this.hash >> 16),
         (byte)(this.hash >> 24),
         (byte)(this.hash >> 32),
         (byte)(this.hash >> 40),
         (byte)(this.hash >> 48),
         (byte)(this.hash >> 56)
      };
   }

    int asInt() {
      return (int)this.hash;
   }

    long asLong() {
      return this.hash;
   }

    long padToLong() {
      return this.hash;
   }

    void writeBytesToImpl(byte[] dest, int offset, int maxLength) {
      for (int i = 0; i < maxLength; i++) {
         dest[offset + i] = (byte)(this.hash >> i * 8);
      }
   }

    bool equalsSameBits(HashCode that) {
      return this.hash == that.asLong();
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
