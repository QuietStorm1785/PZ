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


class Doubles {
public:
   static const Doubles$DoubleConverter INSTANCE = new Doubles$DoubleConverter();
    static const long serialVersionUID = 1L;

   private Doubles$DoubleConverter() {
   }

    double doForward(const std::string& value) {
      return double.valueOf(value);
   }

    std::string doBackward(double value) {
      return value;
   }

    std::string toString() {
      return "Doubles.stringConverter()";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
