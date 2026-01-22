#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/TreeRangeMap/RangeMapEntry.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/1/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   TreeRangeMap$SubRangeMap$1(SubRangeMap var1) {
      super(var1);
      this.this$1 = var1;
   }

   Iterator<Entry<Range<K>, V>> entryIterator() {
      if (SubRangeMap.access$200(this.this$1).empty()) {
         return Iterators.emptyIterator();
      } else {
         Iterator<RangeMapEntry<K, V>> backingItr = TreeRangeMap.access$000(this.this$1.this$0)
            .headMap(SubRangeMap.access$200(this.this$1).upperBound, false)
            .descendingMap()
            .values()
            .iterator();
         return std::make_shared<1>(this, backingItr);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
