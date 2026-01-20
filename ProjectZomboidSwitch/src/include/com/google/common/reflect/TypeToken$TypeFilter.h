#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


enum class TypeToken {
   IGNORE_TYPE_VARIABLE_OR_WILDCARD,
   INTERFACE_ONLY;

   private TypeToken$TypeFilter() {
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
