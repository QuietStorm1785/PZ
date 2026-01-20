#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


enum class Functions {
   INSTANCE;

    void* apply(@Nullable Object) {
    return o;
   }

    std::string toString() {
      return "Functions.identity()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
