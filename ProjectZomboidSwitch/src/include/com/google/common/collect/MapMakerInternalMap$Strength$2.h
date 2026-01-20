#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Equivalence.h"

namespace com {
namespace google {
namespace common {
namespace collect {


enum class MapMakerInternalMap {
   Equivalence<Object> defaultEquivalence() {
      return Equivalence.identity();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
