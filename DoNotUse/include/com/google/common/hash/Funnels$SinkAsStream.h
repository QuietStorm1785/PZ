#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Funnels {
public:
    const PrimitiveSink sink;

   Funnels$SinkAsStream(PrimitiveSink sink) {
      this.sink = (PrimitiveSink)Preconditions.checkNotNull(sink);
   }

    void write(int b) {
      this.sink.putByte((byte)b);
   }

    void write(byte[] bytes) {
      this.sink.putBytes(bytes);
   }

    void write(byte[] bytes, int off, int len) {
      this.sink.putBytes(bytes, off, len);
   }

    std::string toString() {
      return "Funnels.asOutputStream(" + this.sink + ")";
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
