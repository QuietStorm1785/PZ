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
namespace reflect {

enum class TypeToken {
    bool apply(TypeToken<?> type) {
      return type.getRawType().isInterface();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
