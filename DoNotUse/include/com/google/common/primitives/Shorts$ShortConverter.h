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


class Shorts {
public:
   static const Shorts$ShortConverter INSTANCE = new Shorts$ShortConverter();
    static const long serialVersionUID = 1L;

   private Shorts$ShortConverter() {
   }

    short doForward(const std::string& value) {
      return int16_t.decode(value);
   }

    std::string doBackward(short value) {
      return value;
   }

    std::string toString() {
      return "Shorts.stringConverter()";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
