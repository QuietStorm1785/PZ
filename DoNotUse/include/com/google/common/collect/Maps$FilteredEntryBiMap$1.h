#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$FilteredEntryBiMap$1(Predicate var1) {
      this.val$forwardPredicate = var1;
   }

    bool apply(K> input) {
      return this.val$forwardPredicate.apply(Maps.immutableEntry(input.getValue(), input.getKey()));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
