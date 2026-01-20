#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/FilteredEntryMultimap/Keys/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   FilteredEntryMultimap$Keys$1$1(1 var1, Predicate var2) {
      this.this$2 = var1;
      this.val$predicate = var2;
   }

    bool apply(Collection<V>> entry) {
      return this.val$predicate.apply(Multisets.immutableEntry(entry.getKey(), ((Collection)entry.getValue()).size()));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
