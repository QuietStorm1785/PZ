#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeRangeMap/RangeMapEntry.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   TreeRangeMap$SubRangeMap$SubRangeMapAsMap$3(SubRangeMapAsMap var1, Iterator var2) {
      this.this$2 = var1;
      this.val$backingItr = var2;
   }

   protected Entry<Range<K>, V> computeNext() {
      while (this.val$backingItr.hasNext()) {
         RangeMapEntry<K, V> entry = (RangeMapEntry<K, V>)this.val$backingItr.next();
         if (entry.getLowerBound().compareTo(SubRangeMap.access$200(this.this$2.this$1).upperBound) >= 0) {
            return (Entry<Range<K>, V>)this.endOfData();
         }

         if (entry.getUpperBound().compareTo(SubRangeMap.access$200(this.this$2.this$1).lowerBound) > 0) {
            return Maps.immutableEntry(entry.getKey().intersection(SubRangeMap.access$200(this.this$2.this$1)), entry.getValue());
         }
      }

      return (Entry<Range<K>, V>)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
