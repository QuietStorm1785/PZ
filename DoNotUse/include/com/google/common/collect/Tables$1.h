#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Tables {
public:
   public Map<Object, Object> apply(Map<Object, Object> input) {
      return Collections.unmodifiableMap(input);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
