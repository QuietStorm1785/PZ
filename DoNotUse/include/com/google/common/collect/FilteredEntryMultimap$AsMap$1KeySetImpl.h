#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/FilteredEntryMultimap/AsMap.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   FilteredEntryMultimap$AsMap$1KeySetImpl(AsMap var1) {
      super(var1);
      this.this$1 = var1;
   }

    bool removeAll(Collection<?> c) {
      return this.this$1.this$0.removeEntriesIf(Maps.keyPredicateOnEntries(Predicates.in(c)));
   }

    bool retainAll(Collection<?> c) {
      return this.this$1.this$0.removeEntriesIf(Maps.keyPredicateOnEntries(Predicates.not(Predicates.in(c))));
   }

    bool remove(@Nullable Object) {
      return this.this$1.remove(o) != nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
