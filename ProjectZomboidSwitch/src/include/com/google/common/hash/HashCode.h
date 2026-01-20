#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/HashCode/BytesHashCode.h"
#include "com/google/common/hash/HashCode/IntHashCode.h"
#include "com/google/common/hash/HashCode/LongHashCode.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace hash {


class HashCode {
public:
   private static const char[] hexDigits = "0123456789abcdef".toCharArray();

   HashCode() {
   }

   public abstract int bits();

   public abstract int asInt();

   public abstract long asLong();

   public abstract long padToLong();

   public abstract byte[] asBytes();

    int writeBytesTo(byte[] dest, int offset, int maxLength) {
      maxLength = Ints.min(new int[]{maxLength, this.bits() / 8});
      Preconditions.checkPositionIndexes(offset, offset + maxLength, dest.length);
      this.writeBytesToImpl(dest, offset, maxLength);
    return maxLength;
   }

   abstract void writeBytesToImpl(byte[] var1, int var2, int var3);

   byte[] getBytesInternal() {
      return this.asBytes();
   }

   abstract boolean equalsSameBits(HashCode var1);

    static HashCode fromInt(int hash) {
      return std::make_shared<IntHashCode>(hash);
   }

    static HashCode fromLong(long hash) {
      return std::make_shared<LongHashCode>(hash);
   }

    static HashCode fromBytes(byte[] bytes) {
      Preconditions.checkArgument(bytes.length >= 1, "A HashCode must contain at least 1 byte.");
    return fromBytesNoCopy();
   }

    static HashCode fromBytesNoCopy(byte[] bytes) {
      return std::make_shared<BytesHashCode>(bytes);
   }

    static HashCode fromString(const std::string& string) {
      Preconditions.checkArgument(string.length() >= 2, "input string (%s) must have at least 2 characters", string);
      Preconditions.checkArgument(string.length() % 2 == 0, "input string (%s) must have an even number of characters", string);
      byte[] bytes = new byte[string.length() / 2];

      for (int i = 0; i < string.length(); i += 2) {
    int ch1 = decode(string.charAt(i)) << 4;
    int ch2 = decode(string.charAt(i + 1));
         bytes[i / 2] = (byte)(ch1 + ch2);
      }

    return fromBytesNoCopy();
   }

    static int decode(char ch) {
      if (ch >= '0' && ch <= '9') {
         return ch - 48;
      } else if (ch >= 'a' && ch <= 'f') {
         return ch - 97 + 10;
      } else {
         throw IllegalArgumentException("Illegal hexadecimal character: " + ch);
      }
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<HashCode*>(object) != nullptr)) {
    return false;
      } else {
    HashCode that = (HashCode)object;
         return this.bits() == that.bits() && this.equalsSameBits(that);
      }
   }

    int hashCode() {
      if (this.bits() >= 32) {
         return this.asInt();
      } else {
         byte[] bytes = this.getBytesInternal();
    int val = bytes[0] & 255;

         for (int i = 1; i < bytes.length; i++) {
            val |= (bytes[i] & 255) << i * 8;
         }

    return val;
      }
   }

    std::string toString() {
      byte[] bytes = this.getBytesInternal();
    std::stringstream sb = new std::stringstream(2 * bytes.length);

    for (auto& b : bytes)         sb.append(hexDigits[b >> 4 & 15]).append(hexDigits[b & 15]);
      }

      return sb;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
