#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/FilteredEntryMultimap/AsMap.h"
#include "com/google/common/collect/FilteredEntryMultimap/AsMap/1EntrySetImpl/1.h"
#include "com/google/common/collect/Maps/EntrySet.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   FilteredEntryMultimap$AsMap$1EntrySetImpl(AsMap var1) {
      this.this$1 = var1;
   }

   Map<K, Collection<V>> map() {
      return this.this$1;
   }

   public Iterator<Entry<K, Collection<V>>> iterator() {
      return std::make_shared<1>(this);
   }

    bool removeAll(Collection<?> c) {
      return this.this$1.this$0.removeEntriesIf(Predicates.in(c));
   }

    bool retainAll(Collection<?> c) {
      return this.this$1.this$0.removeEntriesIf(Predicates.not(Predicates.in(c)));
   }

    int size() {
      return Iterators.size(this.iterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
