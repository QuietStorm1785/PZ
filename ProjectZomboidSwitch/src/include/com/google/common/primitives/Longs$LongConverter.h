#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Converter.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace primitives {


class Longs {
public:
   static const Longs$LongConverter INSTANCE = new Longs$LongConverter();
    static const long serialVersionUID = 1L;

   private Longs$LongConverter() {
   }

    long doForward(const std::string& value) {
      return int64_t.decode(value);
   }

    std::string doBackward(long value) {
      return value;
   }

    std::string toString() {
      return "Longs.stringConverter()";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
