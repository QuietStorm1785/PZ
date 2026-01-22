#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeRangeMap/RangeMapEntry.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   TreeRangeMap$SubRangeMap$1$1(1 var1, Iterator var2) {
      this.this$2 = var1;
      this.val$backingItr = var2;
   }

   protected Entry<Range<K>, V> computeNext() {
      if (this.val$backingItr.hasNext()) {
         RangeMapEntry<K, V> entry = (RangeMapEntry<K, V>)this.val$backingItr.next();
         return entry.getUpperBound().compareTo(SubRangeMap.access$200(this.this$2.this$1).lowerBound) <= 0
            ? (Entry)this.endOfData()
            : Maps.immutableEntry(entry.getKey().intersection(SubRangeMap.access$200(this.this$2.this$1)), entry.getValue());
      } else {
         return (Entry<Range<K>, V>)this.endOfData();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
