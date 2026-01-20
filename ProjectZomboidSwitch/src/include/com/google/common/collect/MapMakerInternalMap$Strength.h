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
   STRONG,
   WEAK;

   private MapMakerInternalMap$Strength() {
   }

   abstract Equivalence<Object> defaultEquivalence();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
