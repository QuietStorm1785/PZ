#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
    const K key;

   FilteredEntryMultimap$ValuePredicate(K var1, Object key) {
      this.this$0 = var1;
      this.key = key;
   }

    bool apply(@Nullable V) {
      return FilteredEntryMultimap.access$000(this.this$0, this.key, value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
