#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/EntryTransformer.h"
#include "com/google/common/collect/Maps/TransformedEntriesMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   protected SortedMap<K, V1> fromMap() {
      return (SortedMap<K, V1>)this.fromMap;
   }

   Maps$TransformedEntriesSortedMap(SortedMap<K, V1> fromMap, EntryTransformer<? super K, ? super V1, V2> transformer) {
      super(fromMap, transformer);
   }

   public Comparator<? super K> comparator() {
      return this.fromMap().comparator();
   }

    K firstKey() {
      return this.fromMap().firstKey();
   }

   public SortedMap<K, V2> headMap(K toKey) {
      return Maps.transformEntries(this.fromMap().headMap(toKey), this.transformer);
   }

    K lastKey() {
      return this.fromMap().lastKey();
   }

   public SortedMap<K, V2> subMap(K fromKey, K toKey) {
      return Maps.transformEntries(this.fromMap().subMap(fromKey, toKey), this.transformer);
   }

   public SortedMap<K, V2> tailMap(K fromKey) {
      return Maps.transformEntries(this.fromMap().tailMap(fromKey), this.transformer);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
