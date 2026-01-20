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


enum class Predicates {
    bool apply(@Nullable Object) {
    return true;
   }

    std::string toString() {
      return "Predicates.alwaysTrue()";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
