#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class Escapers {
public:
    std::string escape(const std::string& string) {
      return (std::string)Preconditions.checkNotNull(string);
   }

   protected char[] escape(char c) {
    return nullptr;
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
