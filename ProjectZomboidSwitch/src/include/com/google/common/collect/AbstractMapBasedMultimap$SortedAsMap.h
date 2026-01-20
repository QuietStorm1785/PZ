#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultimap/SortedKeySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   SortedSet<K> sortedKeySet;

   AbstractMapBasedMultimap$SortedAsMap(SortedMap<K, Collection<V>> var1, SortedMap submap) {
      super(var1, submap);
      this.this$0 = var1;
   }

   SortedMap<K, Collection<V>> sortedMap() {
      return (SortedMap<K, Collection<V>>)this.submap;
   }

   public Comparator<? super K> comparator() {
      return this.sortedMap().comparator();
   }

    K firstKey() {
      return (K)this.sortedMap().firstKey();
   }

    K lastKey() {
      return (K)this.sortedMap().lastKey();
   }

   public SortedMap<K, Collection<V>> headMap(K toKey) {
      return new AbstractMapBasedMultimap$SortedAsMap(this.this$0, this.sortedMap().headMap(toKey));
   }

   public SortedMap<K, Collection<V>> subMap(K fromKey, K toKey) {
      return new AbstractMapBasedMultimap$SortedAsMap(this.this$0, this.sortedMap().subMap(fromKey, toKey));
   }

   public SortedMap<K, Collection<V>> tailMap(K fromKey) {
      return new AbstractMapBasedMultimap$SortedAsMap(this.this$0, this.sortedMap().tailMap(fromKey));
   }

   public SortedSet<K> keySet() {
      SortedSet<K> result = this.sortedKeySet;
    return result = = nullptr ? (this.sortedKeySet = this.createKeySet()) : result;
   }

   SortedSet<K> createKeySet() {
      return std::make_shared<SortedKeySet>(this.this$0, this.sortedMap());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
