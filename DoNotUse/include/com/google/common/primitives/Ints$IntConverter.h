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


class Ints {
public:
   static const Ints$IntConverter INSTANCE = new Ints$IntConverter();
    static const long serialVersionUID = 1L;

   private Ints$IntConverter() {
   }

    int doForward(const std::string& value) {
      return int.decode(value);
   }

    std::string doBackward(int value) {
      return value;
   }

    std::string toString() {
      return "Ints.stringConverter()";
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
