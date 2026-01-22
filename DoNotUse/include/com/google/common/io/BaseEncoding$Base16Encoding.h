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
   const char[] encoding = new char[512];

   BaseEncoding$Base16Encoding(std::string name, std::string alphabetChars) {
      this(std::make_shared<Alphabet>(name, alphabetChars.toCharArray()));
   }

   private BaseEncoding$Base16Encoding(Alphabet alphabet) {
      super(alphabet, nullptr);
      Preconditions.checkArgument(Alphabet.access$000(alphabet).length == 16);

      for (int i = 0; i < 256; i++) {
         this.encoding[i] = alphabet.encode(i >>> 4);
         this.encoding[i | 256] = alphabet.encode(i & 15);
      }
   }

    void encodeTo(Appendable target, byte[] bytes, int off, int len) {
      Preconditions.checkNotNull(target);
      Preconditions.checkPositionIndexes(off, off + len, bytes.length);

      for (int i = 0; i < len; i++) {
    int b = bytes[off + i] & 255;
         target.append(this.encoding[b]);
         target.append(this.encoding[b | 256]);
      }
   }

    int decodeTo(byte[] target, CharSequence chars) {
      Preconditions.checkNotNull(target);
      if (chars.length() % 2 == 1) {
         throw DecodingException("Invalid input length " + chars.length());
      } else {
    int bytesWritten = 0;

         for (int i = 0; i < chars.length(); i += 2) {
    int decoded = this.alphabet.decode(chars.charAt(i)) << 4 | this.alphabet.decode(chars.charAt(i + 1));
            target[bytesWritten++] = (byte)decoded;
         }

    return bytesWritten;
      }
   }

    BaseEncoding newInstance(Alphabet alphabet, @Nullable char) {
      return new BaseEncoding$Base16Encoding(alphabet);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
