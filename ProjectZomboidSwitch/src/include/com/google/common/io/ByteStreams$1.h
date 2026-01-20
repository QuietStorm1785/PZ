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
namespace io {


class ByteStreams {
public:
    void write(int b) {
   }

    void write(byte[] b) {
      Preconditions.checkNotNull(b);
   }

    void write(byte[] b, int off, int len) {
      Preconditions.checkNotNull(b);
   }

    std::string toString() {
      return "ByteStreams.nullOutputStream()";
   }
}
} // namespace io
} // namespace common
} // namespace google
} // namespace com
