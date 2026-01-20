#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/EntrySet.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   TreeRangeMap$SubRangeMap$SubRangeMapAsMap$2(SubRangeMapAsMap var1) {
      this.this$2 = var1;
   }

   Map<Range<K>, V> map() {
      return this.this$2;
   }

   public Iterator<Entry<Range<K>, V>> iterator() {
      return this.this$2.entryIterator();
   }

    bool retainAll(Collection<?> c) {
      return SubRangeMapAsMap.access$300(this.this$2, Predicates.not(Predicates.in(c)));
   }

    int size() {
      return Iterators.size(this.iterator());
   }

    bool isEmpty() {
      return !this.iterator().hasNext();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
