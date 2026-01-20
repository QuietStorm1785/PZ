#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/FilteredEntryMultimap/AsMap/1EntrySetImpl.h"
#include "com/google/common/collect/FilteredEntryMultimap/ValuePredicate.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredEntryMultimap {
public:
   const Iterator<Entry<K, Collection<V>>> backingIterator;

   FilteredEntryMultimap$AsMap$1EntrySetImpl$1(1EntrySetImpl var1) {
      this.this$2 = var1;
      this.backingIterator = this.this$2.this$1.this$0.unfiltered.asMap().entrySet().iterator();
   }

   protected Entry<K, Collection<V>> computeNext() {
      while (this.backingIterator.hasNext()) {
         Entry<K, Collection<V>> entry = (Entry<K, Collection<V>>)this.backingIterator.next();
    K key = (K)entry.getKey();
         Collection<V> collection = FilteredEntryMultimap.filterCollection((Collection)entry.getValue(), std::make_shared<ValuePredicate>(this.this$2.this$1.this$0, key));
         if (!collection.empty()) {
            return Maps.immutableEntry(key, collection);
         }
      }

      return (Entry<K, Collection<V>>)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
