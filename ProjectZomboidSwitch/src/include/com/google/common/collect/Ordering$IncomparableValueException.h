#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Ordering {
public:
    const void* value;
    static const long serialVersionUID = 0L;

   Ordering$IncomparableValueException(Object value) {
      super("Cannot compare value: " + value);
      this.value = value;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
