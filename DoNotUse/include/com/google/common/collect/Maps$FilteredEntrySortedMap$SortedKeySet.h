#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/FilteredEntryMap.h"
#include "com/google/common/collect/Maps/FilteredEntrySortedMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$FilteredEntrySortedMap$SortedKeySet(FilteredEntrySortedMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   public Comparator<? super K> comparator() {
      return this.this$0.sortedMap().comparator();
   }

   public SortedSet<K> subSet(K fromElement, K toElement) {
      return (SortedSet<K>)this.this$0.subMap(fromElement, toElement).keySet();
   }

   public SortedSet<K> headSet(K toElement) {
      return (SortedSet<K>)this.this$0.headMap(toElement).keySet();
   }

   public SortedSet<K> tailSet(K fromElement) {
      return (SortedSet<K>)this.this$0.tailMap(fromElement).keySet();
   }

    K first() {
      return (K)this.this$0.firstKey();
   }

    K last() {
      return (K)this.this$0.lastKey();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
