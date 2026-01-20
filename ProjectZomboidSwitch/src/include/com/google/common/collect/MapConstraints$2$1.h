#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapConstraints/2.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapConstraints {
public:
   MapConstraints$2$1(2 var1) {
      this.this$0 = var1;
   }

    V checkElement(V value) {
      this.this$0.val$constraint.checkKeyValue(this.this$0.getKey(), value);
    return value;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
