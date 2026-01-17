#pragma once
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ByteBufferBackedInputStream : public InputStream {
public:
  const ByteBuffer buf;

public
  ByteBufferBackedInputStream(ByteBuffer byteBuffer) {
    Objects.requireNonNull(byteBuffer);
    this.buf = byteBuffer;
  }

  int read() { return !this.buf.hasRemaining() ? -1 : this.buf.get() & 0xFF; }

  int read(byte[] bytes, int int1, int int0) {
    if (!this.buf.hasRemaining()) {
      return -1;
    } else {
      int0 = Math.min(int0, this.buf.remaining());
      this.buf.get(bytes, int1, int0);
      return int0;
    }
  }
}
} // namespace util
} // namespace zombie
