#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace util {


class ByteBufferBackedInputStream : public InputStream {
public:
    const ByteBuffer buf;

    public ByteBufferBackedInputStream(ByteBuffer var1) {
      Objects.requireNonNull(var1);
      this.buf = var1;
   }

    int read() {
      return !this.buf.hasRemaining() ? -1 : this.buf.get() & 0xFF;
   }

    int read(byte[] var1, int var2, int var3) {
      if (!this.buf.hasRemaining()) {
         return -1;
      } else {
         var3 = Math.min(var3, this.buf.remaining());
         this.buf.get(var1, var2, var3);
    return var3;
      }
   }
}
} // namespace util
} // namespace zombie
