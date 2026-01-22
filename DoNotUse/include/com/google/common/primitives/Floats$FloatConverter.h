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


class Floats {
public:
   static const Floats$FloatConverter INSTANCE = new Floats$FloatConverter();
    static const long serialVersionUID = 1L;

   private Floats$FloatConverter() {
   }

    float doForward(const std::string& value) {
      return float.valueOf(value);
   }

    std::string doBackward(float value) {
      return value;
   }

    std::string toString() {
      return "Floats.stringConverter()";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
