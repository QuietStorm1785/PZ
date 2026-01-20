#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/hash/AbstractNonStreamingHashFunction/ExposedByteArrayOutputStream.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class AbstractNonStreamingHashFunction {
public:
    const ExposedByteArrayOutputStream stream;
    static const int BOTTOM_BYTE = 255;

   AbstractNonStreamingHashFunction$BufferingHasher(AbstractNonStreamingHashFunction var1, int expectedInputSize) {
      this.this$0 = var1;
      this.stream = std::make_shared<ExposedByteArrayOutputStream>(expectedInputSize);
   }

    Hasher putByte(uint8_t b) {
      this.stream.write(b);
    return this;
   }

    Hasher putBytes(byte[] bytes) {
      try {
         this.stream.write(bytes);
    return this;
      } catch (IOException var3) {
         throw RuntimeException(var3);
      }
   }

    Hasher putBytes(byte[] bytes, int off, int len) {
      this.stream.write(bytes, off, len);
    return this;
   }

    Hasher putShort(short s) {
      this.stream.write(s & 255);
      this.stream.write(s >>> 8 & 0xFF);
    return this;
   }

    Hasher putInt(int i) {
      this.stream.write(i & 0xFF);
      this.stream.write(i >>> 8 & 0xFF);
      this.stream.write(i >>> 16 & 0xFF);
      this.stream.write(i >>> 24 & 0xFF);
    return this;
   }

    Hasher putLong(long l) {
      for (int i = 0; i < 64; i += 8) {
         this.stream.write((byte)(l >>> i & 255L));
      }

    return this;
   }

    Hasher putChar(char c) {
      this.stream.write(c & 255);
      this.stream.write(c >>> '\b' & 0xFF);
    return this;
   }

   public <T> Hasher putObject(T instance, Funnel<? super T> funnel) {
      funnel.funnel(instance, this);
    return this;
   }

    HashCode hash() {
      return this.this$0.hashBytes(this.stream.byteArray(), 0, this.stream.length());
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
