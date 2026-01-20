#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/FilteredEntryMultimap/Keys.h"
#include "com/google/common/collect/FilteredEntryMultimap/Keys/1/1.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/EntrySet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   FilteredEntryMultimap$Keys$1(Keys var1) {
      this.this$1 = var1;
   }

   Multiset<K> multiset() {
      return this.this$1;
   }

   public Iterator<Entry<K>> iterator() {
      return this.this$1.entryIterator();
   }

    int size() {
      return this.this$1.this$0.keySet().size();
   }

    bool removeEntriesIf(Predicate<? super) {
      return this.this$1.this$0.removeEntriesIf(std::make_shared<1>(this, predicate));
   }

    bool removeAll(Collection<?> c) {
      return this.removeEntriesIf(Predicates.in(c));
   }

    bool retainAll(Collection<?> c) {
      return this.removeEntriesIf(Predicates.not(Predicates.in(c)));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
