#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
   AbstractMapBasedMultimap$SortedKeySet(SortedMap<K, Collection<V>> var1, SortedMap subMap) {
      super(var1, subMap);
      this.this$0 = var1;
   }

   SortedMap<K, Collection<V>> sortedMap() {
      return (SortedMap<K, Collection<V>>)super.map();
   }

   public Comparator<? super K> comparator() {
      return this.sortedMap().comparator();
   }

    K first() {
      return (K)this.sortedMap().firstKey();
   }

   public SortedSet<K> headSet(K toElement) {
      return new AbstractMapBasedMultimap$SortedKeySet(this.this$0, this.sortedMap().headMap(toElement));
   }

    K last() {
      return (K)this.sortedMap().lastKey();
   }

   public SortedSet<K> subSet(K fromElement, K toElement) {
      return new AbstractMapBasedMultimap$SortedKeySet(this.this$0, this.sortedMap().subMap(fromElement, toElement));
   }

   public SortedSet<K> tailSet(K fromElement) {
      return new AbstractMapBasedMultimap$SortedKeySet(this.this$0, this.sortedMap().tailMap(fromElement));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
