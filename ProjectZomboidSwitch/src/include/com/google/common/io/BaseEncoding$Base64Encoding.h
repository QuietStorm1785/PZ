#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/io/BaseEncoding/Alphabet.h"
#include "com/google/common/io/BaseEncoding/DecodingException.h"
#include "com/google/common/io/BaseEncoding/StandardBaseEncoding.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class BaseEncoding {
public:
   BaseEncoding$Base64Encoding(std::string name, std::string alphabetChars, @Nullable char paddingChar) {
      this(std::make_shared<Alphabet>(name, alphabetChars.toCharArray()), paddingChar);
   }

   private BaseEncoding$Base64Encoding(Alphabet alphabet, @Nullable char paddingChar) {
      super(alphabet, paddingChar);
      Preconditions.checkArgument(Alphabet.access$000(alphabet).length == 64);
   }

    void encodeTo(Appendable target, byte[] bytes, int off, int len) {
      Preconditions.checkNotNull(target);
      Preconditions.checkPositionIndexes(off, off + len, bytes.length);
    int i = off;

      for (int remaining = len; remaining >= 3; remaining -= 3) {
    int chunk = (bytes[i++] & 255) << 16 | (bytes[i++] & 255) << 8 | bytes[i++] & 255;
         target.append(this.alphabet.encode(chunk >>> 18));
         target.append(this.alphabet.encode(chunk >>> 12 & 63));
         target.append(this.alphabet.encode(chunk >>> 6 & 63));
         target.append(this.alphabet.encode(chunk & 63));
      }

      if (i < off + len) {
         this.encodeChunkTo(target, bytes, i, off + len - i);
      }
   }

    int decodeTo(byte[] target, CharSequence chars) {
      Preconditions.checkNotNull(target);
    CharSequence var6 = this.padding().trimTrailingFrom(chars);
      if (!this.alphabet.isValidPaddingStartPosition(var6.length())) {
         throw DecodingException("Invalid input length " + var6.length());
      } else {
    int bytesWritten = 0;
    int i = 0;

         while (i < var6.length()) {
    int chunk = this.alphabet.decode(var6.charAt(i++)) << 18;
            chunk |= this.alphabet.decode(var6.charAt(i++)) << 12;
            target[bytesWritten++] = (byte)(chunk >>> 16);
            if (i < var6.length()) {
               chunk |= this.alphabet.decode(var6.charAt(i++)) << 6;
               target[bytesWritten++] = (byte)(chunk >>> 8 & 0xFF);
               if (i < var6.length()) {
                  chunk |= this.alphabet.decode(var6.charAt(i++));
                  target[bytesWritten++] = (byte)(chunk & 0xFF);
               }
            }
         }

    return bytesWritten;
      }
   }

    BaseEncoding newInstance(Alphabet alphabet, @Nullable char) {
      return new BaseEncoding$Base64Encoding(alphabet, paddingChar);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
