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
namespace hash {


class AbstractNonStreamingHashFunction {
public:
   AbstractNonStreamingHashFunction$ExposedByteArrayOutputStream(int expectedInputSize) {
      super(expectedInputSize);
   }

   byte[] byteArray() {
      return this.buf;
   }

    int length() {
      return this.count;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
