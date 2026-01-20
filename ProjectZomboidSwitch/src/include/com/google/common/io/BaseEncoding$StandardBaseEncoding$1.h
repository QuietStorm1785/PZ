#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
    int writtenChars;

   BaseEncoding$StandardBaseEncoding$1(StandardBaseEncoding var1, Writer var2) {
      this.this$0 = var1;
      this.val$out = var2;
      this.bitBuffer = 0;
      this.bitBufferLength = 0;
      this.writtenChars = 0;
   }

    void write(int b) {
      this.bitBuffer <<= 8;
      this.bitBuffer |= b & 0xFF;

      for (this.bitBufferLength += 8;
         this.bitBufferLength >= this.this$0.alphabet.bitsPerChar;
         this.bitBufferLength = this.bitBufferLength - this.this$0.alphabet.bitsPerChar
      ) {
    int charIndex = this.bitBuffer >> this.bitBufferLength - this.this$0.alphabet.bitsPerChar & this.this$0.alphabet.mask;
         this.val$out.write(this.this$0.alphabet.encode(charIndex));
         this.writtenChars++;
      }
   }

    void flush() {
      this.val$out.flush();
   }

    void close() {
      if (this.bitBufferLength > 0) {
    int charIndex = this.bitBuffer << this.this$0.alphabet.bitsPerChar - this.bitBufferLength & this.this$0.alphabet.mask;
         this.val$out.write(this.this$0.alphabet.encode(charIndex));
         this.writtenChars++;
         if (this.this$0.paddingChar != nullptr) {
            while (this.writtenChars % this.this$0.alphabet.charsPerChunk != 0) {
               this.val$out.write(this.this$0.paddingChar);
               this.writtenChars++;
            }
         }
      }

      this.val$out.close();
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
