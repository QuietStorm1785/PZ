#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/FilteredMultiset.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   Multisets$FilteredMultiset$1(FilteredMultiset var1) {
      this.this$0 = var1;
   }

    bool apply(Entry<E> entry) {
      return this.this$0.predicate.apply(entry.getElement());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
