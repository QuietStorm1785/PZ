#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/ConstrainedMultimap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$ConstrainedMultimap$1(ConstrainedMultimap var1, Object var2) {
      this.this$0 = var1;
      this.val$key = var2;
   }

    V checkElement(V value) {
      this.this$0.constraint.checkKeyValue(this.val$key, value);
    return value;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
