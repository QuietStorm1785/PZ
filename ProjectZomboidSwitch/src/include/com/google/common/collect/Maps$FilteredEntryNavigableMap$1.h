#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/FilteredEntryNavigableMap.h"
#include "com/google/common/collect/Maps/NavigableKeySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$FilteredEntryNavigableMap$1(FilteredEntryNavigableMap var1, NavigableMap x0) {
      super(x0);
      this.this$0 = var1;
   }

    bool removeAll(Collection<?> c) {
      return Iterators.removeIf(
         FilteredEntryNavigableMap.access$700(this.this$0).entrySet().iterator(),
         Predicates.and(FilteredEntryNavigableMap.access$600(this.this$0), Maps.keyPredicateOnEntries(Predicates.in(c)))
      );
   }

    bool retainAll(Collection<?> c) {
      return Iterators.removeIf(
         FilteredEntryNavigableMap.access$700(this.this$0).entrySet().iterator(),
         Predicates.and(FilteredEntryNavigableMap.access$600(this.this$0), Maps.keyPredicateOnEntries(Predicates.not(Predicates.in(c))))
      );
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
