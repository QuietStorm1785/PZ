#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class HashCode {
public:
   const byte[] bytes;
    static const long serialVersionUID = 0L;

   HashCode$BytesHashCode(byte[] bytes) {
      this.bytes = (byte[])Preconditions.checkNotNull(bytes);
   }

    int bits() {
      return this.bytes.length * 8;
   }

   public byte[] asBytes() {
      return (byte[])this.bytes.clone();
   }

    int asInt() {
      Preconditions.checkState(this.bytes.length >= 4, "HashCode#asInt() requires >= 4 bytes (it only has %s bytes).", this.bytes.length);
      return this.bytes[0] & 0xFF | (this.bytes[1] & 0xFF) << 8 | (this.bytes[2] & 0xFF) << 16 | (this.bytes[3] & 0xFF) << 24;
   }

    long asLong() {
      Preconditions.checkState(this.bytes.length >= 8, "HashCode#asLong() requires >= 8 bytes (it only has %s bytes).", this.bytes.length);
      return this.padToLong();
   }

    long padToLong() {
    long retVal = this.bytes[0] & 255;

      for (int i = 1; i < Math.min(this.bytes.length, 8); i++) {
         retVal |= (this.bytes[i] & 255L) << i * 8;
      }

    return retVal;
   }

    void writeBytesToImpl(byte[] dest, int offset, int maxLength) {
      System.arraycopy(this.bytes, 0, dest, offset, maxLength);
   }

   byte[] getBytesInternal() {
      return this.bytes;
   }

    bool equalsSameBits(HashCode that) {
      if (this.bytes.length != that.getBytesInternal().length) {
    return false;
      } else {
    bool areEqual = true;

         for (int i = 0; i < this.bytes.length; i++) {
            areEqual &= this.bytes[i] == that.getBytesInternal()[i];
         }

    return areEqual;
      }
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
