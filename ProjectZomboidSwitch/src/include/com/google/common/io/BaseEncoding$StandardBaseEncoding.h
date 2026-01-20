#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/CharMatcher.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/BaseEncoding/Alphabet.h"
#include "com/google/common/io/BaseEncoding/DecodingException.h"
#include "com/google/common/io/BaseEncoding/SeparatedBaseEncoding.h"
#include "com/google/common/io/BaseEncoding/StandardBaseEncoding/1.h"
#include "com/google/common/io/BaseEncoding/StandardBaseEncoding/2.h"
#include "com/google/common/math/IntMath.h"
#include "java/math/RoundingMode.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class BaseEncoding {
public:
    const Alphabet alphabet;
    const char paddingChar;
   private transient BaseEncoding upperCase;
   private transient BaseEncoding lowerCase;

   BaseEncoding$StandardBaseEncoding(std::string name, std::string alphabetChars, @Nullable char paddingChar) {
      this(std::make_shared<Alphabet>(name, alphabetChars.toCharArray()), paddingChar);
   }

   BaseEncoding$StandardBaseEncoding(Alphabet alphabet, @Nullable char paddingChar) {
      this.alphabet = (Alphabet)Preconditions.checkNotNull(alphabet);
      Preconditions.checkArgument(paddingChar == nullptr || !alphabet.matches(paddingChar), "Padding character %s was already in alphabet", paddingChar);
      this.paddingChar = paddingChar;
   }

    CharMatcher padding() {
      return this.paddingChar == nullptr ? CharMatcher.none() : CharMatcher.is(this.paddingChar);
   }

    int maxEncodedSize(int bytes) {
      return this.alphabet.charsPerChunk * IntMath.divide(bytes, this.alphabet.bytesPerChunk, RoundingMode.CEILING);
   }

    OutputStream encodingStream(Writer out) {
      Preconditions.checkNotNull(out);
      return std::make_shared<1>(this, out);
   }

    void encodeTo(Appendable target, byte[] bytes, int off, int len) {
      Preconditions.checkNotNull(target);
      Preconditions.checkPositionIndexes(off, off + len, bytes.length);
    int i = 0;

      while (i < len) {
         this.encodeChunkTo(target, bytes, off + i, Math.min(this.alphabet.bytesPerChunk, len - i));
         i += this.alphabet.bytesPerChunk;
      }
   }

    void encodeChunkTo(Appendable target, byte[] bytes, int off, int len) {
      Preconditions.checkNotNull(target);
      Preconditions.checkPositionIndexes(off, off + len, bytes.length);
      Preconditions.checkArgument(len <= this.alphabet.bytesPerChunk);
    long bitBuffer = 0L;

      for (int i = 0; i < len; i++) {
         bitBuffer |= bytes[off + i] & 255;
         bitBuffer <<= 8;
      }

    int bitOffset = (len + 1) * 8 - this.alphabet.bitsPerChar;

    int bitsProcessed;
      for (bitsProcessed = 0; bitsProcessed < len * 8; bitsProcessed += this.alphabet.bitsPerChar) {
    int charIndex = (int)(bitBuffer >>> bitOffset - bitsProcessed) & this.alphabet.mask;
         target.append(this.alphabet.encode(charIndex));
      }

      if (this.paddingChar != nullptr) {
         while (bitsProcessed < this.alphabet.bytesPerChunk * 8) {
            target.append(this.paddingChar);
            bitsProcessed += this.alphabet.bitsPerChar;
         }
      }
   }

    int maxDecodedSize(int chars) {
      return (int)(((long)this.alphabet.bitsPerChar * chars + 7L) / 8L);
   }

    bool canDecode(CharSequence chars) {
    CharSequence var3 = this.padding().trimTrailingFrom(chars);
      if (!this.alphabet.isValidPaddingStartPosition(var3.length())) {
    return false;
      } else {
         for (int i = 0; i < var3.length(); i++) {
            if (!this.alphabet.canDecode(var3.charAt(i))) {
    return false;
            }
         }

    return true;
      }
   }

    int decodeTo(byte[] target, CharSequence chars) {
      Preconditions.checkNotNull(target);
    CharSequence var10 = this.padding().trimTrailingFrom(chars);
      if (!this.alphabet.isValidPaddingStartPosition(var10.length())) {
         throw DecodingException("Invalid input length " + var10.length());
      } else {
    int bytesWritten = 0;

         for (int charIdx = 0; charIdx < var10.length(); charIdx += this.alphabet.charsPerChunk) {
    long chunk = 0L;
    int charsProcessed = 0;

            for (int i = 0; i < this.alphabet.charsPerChunk; i++) {
               chunk <<= this.alphabet.bitsPerChar;
               if (charIdx + i < var10.length()) {
                  chunk |= this.alphabet.decode(var10.charAt(charIdx + charsProcessed++));
               }
            }

    int minOffset = this.alphabet.bytesPerChunk * 8 - charsProcessed * this.alphabet.bitsPerChar;

            for (int offset = (this.alphabet.bytesPerChunk - 1) * 8; offset >= minOffset; offset -= 8) {
               target[bytesWritten++] = (byte)(chunk >>> offset & 255L);
            }
         }

    return bytesWritten;
      }
   }

    InputStream decodingStream(Reader reader) {
      Preconditions.checkNotNull(reader);
      return std::make_shared<2>(this, reader);
   }

    BaseEncoding omitPadding() {
      return (BaseEncoding)(this.paddingChar == nullptr ? this : this.newInstance(this.alphabet, nullptr));
   }

    BaseEncoding withPadChar(char padChar) {
      return (BaseEncoding)(8 % this.alphabet.bitsPerChar != 0 && (this.paddingChar == nullptr || this.paddingChar != padChar)
         ? this.newInstance(this.alphabet, padChar)
         : this);
   }

    BaseEncoding withSeparator(const std::string& separator, int afterEveryChars) {
      Preconditions.checkArgument(
         this.padding().or(this.alphabet).matchesNoneOf(separator), "Separator (%s) cannot contain alphabet or padding characters", separator
      );
      return std::make_shared<SeparatedBaseEncoding>(this, separator, afterEveryChars);
   }

    BaseEncoding upperCase() {
    BaseEncoding result = this.upperCase;
      if (result == nullptr) {
    Alphabet upper = this.alphabet.upperCase();
         result = this.upperCase = (BaseEncoding)(upper == this.alphabet ? this : this.newInstance(upper, this.paddingChar));
      }

    return result;
   }

    BaseEncoding lowerCase() {
    BaseEncoding result = this.lowerCase;
      if (result == nullptr) {
    Alphabet lower = this.alphabet.lowerCase();
         result = this.lowerCase = (BaseEncoding)(lower == this.alphabet ? this : this.newInstance(lower, this.paddingChar));
      }

    return result;
   }

    BaseEncoding newInstance(Alphabet alphabet, @Nullable char) {
      return new BaseEncoding$StandardBaseEncoding(alphabet, paddingChar);
   }

    std::string toString() {
    std::stringstream builder = new std::stringstream("BaseEncoding.");
      builder.append(this.alphabet);
      if (8 % this.alphabet.bitsPerChar != 0) {
         if (this.paddingChar == nullptr) {
            builder.append(".omitPadding()");
         } else {
            builder.append(".withPadChar('").append(this.paddingChar).append("')");
         }
      }

      return builder;
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<BaseEncoding*>(other) != nullptr$StandardBaseEncoding)) {
    return false;
      } else {
         BaseEncoding$StandardBaseEncoding that = (BaseEncoding$StandardBaseEncoding)other;
         return this.alphabet == that.alphabet) && Objects.equal(this.paddingChar, that.paddingChar);
      }
   }

    int hashCode() {
      return this.alphabet.hashCode() ^ Objects.hashCode(new Object[]{this.paddingChar});
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
