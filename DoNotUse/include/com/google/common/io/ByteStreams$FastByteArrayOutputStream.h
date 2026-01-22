#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace io {


class ByteStreams {
public:
   private ByteStreams$FastByteArrayOutputStream() {
   }

    void writeTo(byte[] b, int off) {
      System.arraycopy(this.buf, 0, b, off, this.count);
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
