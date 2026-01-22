#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap.h"
#include "com/google/common/collect/TreeRangeMap/RangeMapEntry.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   const Iterable<Entry<Range<K>, V>> entryIterable;

   TreeRangeMap$AsMapOfRanges(Iterable<RangeMapEntry<K, V>> var1, Iterable entryIterable) {
      this.this$0 = var1;
      this.entryIterable = entryIterable;
   }

    bool containsKey(@Nullable Object) {
      return this.get(key) != nullptr;
   }

    V get(@Nullable Object) {
      if (dynamic_cast<Range*>(key) != nullptr) {
         Range<?> range = (Range<?>)key;
         RangeMapEntry<K, V> rangeMapEntry = (RangeMapEntry<K, V>)TreeRangeMap.access$000(this.this$0).get(range.lowerBound);
         if (rangeMapEntry != nullptr && rangeMapEntry.getKey() == range)) {
            return (V)rangeMapEntry.getValue();
         }
      }

    return nullptr;
   }

    int size() {
      return TreeRangeMap.access$000(this.this$0).size();
   }

   Iterator<Entry<Range<K>, V>> entryIterator() {
      return this.entryIterable.iterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
