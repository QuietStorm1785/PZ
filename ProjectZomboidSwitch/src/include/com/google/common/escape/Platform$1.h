#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace escape {

class Platform {
public:
   protected char[] initialValue() {
      return new char[1024];
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
