#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher.h"
#include "com/google/common/io/BaseEncoding/DecodingException.h"
#include "com/google/common/io/BaseEncoding/StandardBaseEncoding.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class BaseEncoding {
public:
    int bitBuffer;
    int bitBufferLength;
    int readChars;
    bool hitPadding;
    const CharMatcher paddingMatcher;

   BaseEncoding$StandardBaseEncoding$2(StandardBaseEncoding var1, Reader var2) {
      this.this$0 = var1;
      this.val$reader = var2;
      this.bitBuffer = 0;
      this.bitBufferLength = 0;
      this.readChars = 0;
      this.hitPadding = false;
      this.paddingMatcher = this.this$0.padding();
   }

    int read() {
      while (true) {
    int readChar = this.val$reader.read();
         if (readChar == -1) {
            if (!this.hitPadding && !this.this$0.alphabet.isValidPaddingStartPosition(this.readChars)) {
               throw DecodingException("Invalid input length " + this.readChars);
            }

            return -1;
         }

         this.readChars++;
    char ch = (char)readChar;
         if (!this.paddingMatcher.matches(ch)) {
            if (this.hitPadding) {
               throw DecodingException("Expected padding character but found '" + ch + "' at index " + this.readChars);
            }

            this.bitBuffer = this.bitBuffer << this.this$0.alphabet.bitsPerChar;
            this.bitBuffer = this.bitBuffer | this.this$0.alphabet.decode(ch);
            this.bitBufferLength = this.bitBufferLength + this.this$0.alphabet.bitsPerChar;
            if (this.bitBufferLength >= 8) {
               this.bitBufferLength -= 8;
               return this.bitBuffer >> this.bitBufferLength & 0xFF;
            }
         } else {
            if (!this.hitPadding && (this.readChars == 1 || !this.this$0.alphabet.isValidPaddingStartPosition(this.readChars - 1))) {
               throw DecodingException("Padding cannot start at index " + this.readChars);
            }

            this.hitPadding = true;
         }
      }
   }

    void close() {
      this.val$reader.close();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
