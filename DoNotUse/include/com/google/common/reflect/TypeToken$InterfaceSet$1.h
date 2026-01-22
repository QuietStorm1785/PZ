#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/reflect/TypeToken/InterfaceSet.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToken {
public:
   TypeToken$InterfaceSet$1(InterfaceSet var1) {
      this.this$1 = var1;
   }

    bool apply(Class<?> type) {
      return type.isInterface();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
