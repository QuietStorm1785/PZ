#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Ascii.h"
#include "com/google/common/base/CharMatcher.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/BaseEncoding/DecodingException.h"
#include "com/google/common/math/IntMath.h"
#include "java/math/RoundingMode.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace io {


class BaseEncoding {
public:
    const std::string name;
   private const char[] chars;
    const int mask;
    const int bitsPerChar;
    const int charsPerChunk;
    const int bytesPerChunk;
   private const byte[] decodabet;
   private const boolean[] validPadding;

   BaseEncoding$Alphabet(std::string name, char[] chars) {
      this.name = (std::string)Preconditions.checkNotNull(name);
      this.chars = (char[])Preconditions.checkNotNull(chars);

      try {
         this.bitsPerChar = IntMath.log2(chars.length, RoundingMode.UNNECESSARY);
      } catch (ArithmeticException var8) {
         throw IllegalArgumentException("Illegal alphabet length " + chars.length, var8);
      }

    int gcd = Math.min(8, int.lowestOneBit(this.bitsPerChar));

      try {
         this.charsPerChunk = 8 / gcd;
         this.bytesPerChunk = this.bitsPerChar / gcd;
      } catch (ArithmeticException var7) {
         throw IllegalArgumentException("Illegal alphabet " + new std::string(chars), var7);
      }

      this.mask = chars.length - 1;
      byte[] decodabet = new byte[128];
      Arrays.fill(decodabet, (byte)-1);

      for (int i = 0; i < chars.length; i++) {
    char c = chars[i];
         Preconditions.checkArgument(CharMatcher.ascii().matches(c), "Non-ASCII character: %s", c);
         Preconditions.checkArgument(decodabet[c] == -1, "Duplicate character: %s", c);
         decodabet[c] = (byte)i;
      }

      this.decodabet = decodabet;
      boolean[] validPadding = new boolean[this.charsPerChunk];

      for (int i = 0; i < this.bytesPerChunk; i++) {
         validPadding[IntMath.divide(i * 8, this.bitsPerChar, RoundingMode.CEILING)] = true;
      }

      this.validPadding = validPadding;
   }

    char encode(int bits) {
      return this.chars[bits];
   }

    bool isValidPaddingStartPosition(int index) {
      return this.validPadding[index % this.charsPerChunk];
   }

    bool canDecode(char ch) {
      return ch <= 127 && this.decodabet[ch] != -1;
   }

    int decode(char ch) {
      if (ch <= 127 && this.decodabet[ch] != -1) {
         return this.decodabet[ch];
      } else {
         throw DecodingException("Unrecognized character: " + (CharMatcher.invisible().matches(ch) ? "0x" + int.toHexString(ch) : ch));
      }
   }

    bool hasLowerCase() {
      for (char c : this.chars) {
         if (Ascii.isLowerCase(c)) {
    return true;
         }
      }

    return false;
   }

    bool hasUpperCase() {
      for (char c : this.chars) {
         if (Ascii.isUpperCase(c)) {
    return true;
         }
      }

    return false;
   }

   BaseEncoding$Alphabet upperCase() {
      if (!this.hasLowerCase()) {
    return this;
      } else {
         Preconditions.checkState(!this.hasUpperCase(), "Cannot call upperCase() on a mixed-case alphabet");
         char[] upperCased = new char[this.chars.length];

         for (int i = 0; i < this.chars.length; i++) {
            upperCased[i] = Ascii.toUpperCase(this.chars[i]);
         }

         return new BaseEncoding$Alphabet(this.name + ".upperCase()", upperCased);
      }
   }

   BaseEncoding$Alphabet lowerCase() {
      if (!this.hasUpperCase()) {
    return this;
      } else {
         Preconditions.checkState(!this.hasLowerCase(), "Cannot call lowerCase() on a mixed-case alphabet");
         char[] lowerCased = new char[this.chars.length];

         for (int i = 0; i < this.chars.length; i++) {
            lowerCased[i] = Ascii.toLowerCase(this.chars[i]);
         }

         return new BaseEncoding$Alphabet(this.name + ".lowerCase()", lowerCased);
      }
   }

    bool matches(char c) {
      return CharMatcher.ascii().matches(c) && this.decodabet[c] != -1;
   }

    std::string toString() {
      return this.name;
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<BaseEncoding*>(other) != nullptr$Alphabet) {
         BaseEncoding$Alphabet that = (BaseEncoding$Alphabet)other;
         return Arrays == this.chars, that.chars);
      } else {
    return false;
      }
   }

    int hashCode() {
      return Arrays.hashCode(this.chars);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
