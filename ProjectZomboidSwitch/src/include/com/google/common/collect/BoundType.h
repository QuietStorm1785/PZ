#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace collect {


enum class BoundType {
   OPEN,
   CLOSED;

    private BoundType() {
   }

    static BoundType forBoolean(bool inclusive) {
      return inclusive ? CLOSED : OPEN;
   }

   abstract BoundType flip();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
