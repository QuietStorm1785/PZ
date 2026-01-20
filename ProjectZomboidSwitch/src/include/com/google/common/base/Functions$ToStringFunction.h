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
namespace base {

enum class Functions {
   INSTANCE;

    std::string apply(void* o) {
      Preconditions.checkNotNull(o);
      return o;
   }

    std::string toString() {
      return "Functions.toStringFunction()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
