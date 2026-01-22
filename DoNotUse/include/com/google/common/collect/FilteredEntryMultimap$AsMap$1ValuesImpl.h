#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/FilteredEntryMultimap/AsMap.h"
#include "com/google/common/collect/FilteredEntryMultimap/ValuePredicate.h"
#include "com/google/common/collect/Maps/Values.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   FilteredEntryMultimap$AsMap$1ValuesImpl(AsMap var1) {
      super(var1);
      this.this$1 = var1;
   }

    bool remove(@Nullable Object) {
      if (dynamic_cast<Collection*>(o) != nullptr) {
         Collection<?> c = (Collection<?>)o;
         Iterator<Entry<K, Collection<V>>> entryIterator = this.this$1.this$0.unfiltered.asMap().entrySet().iterator();

         while (entryIterator.hasNext()) {
            Entry<K, Collection<V>> entry = (Entry<K, Collection<V>>)entryIterator.next();
    K key = (K)entry.getKey();
            Collection<V> collection = FilteredEntryMultimap.filterCollection((Collection)entry.getValue(), std::make_shared<ValuePredicate>(this.this$1.this$0, key));
            if (!collection.empty() && c == collection)) {
               if (collection.size() == ((Collection)entry.getValue()).size()) {
                  entryIterator.remove();
               } else {
                  collection.clear();
               }

    return true;
            }
         }
      }

    return false;
   }

    bool removeAll(Collection<?> c) {
      return this.this$1.this$0.removeEntriesIf(Maps.valuePredicateOnEntries(Predicates.in(c)));
   }

    bool retainAll(Collection<?> c) {
      return this.this$1.this$0.removeEntriesIf(Maps.valuePredicateOnEntries(Predicates.not(Predicates.in(c))));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
