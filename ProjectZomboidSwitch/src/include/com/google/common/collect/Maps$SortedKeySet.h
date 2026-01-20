#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/KeySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$SortedKeySet(SortedMap<K, V> map) {
      super(map);
   }

   SortedMap<K, V> map() {
      return (SortedMap<K, V>)super.map();
   }

   public Comparator<? super K> comparator() {
      return this.map().comparator();
   }

   public SortedSet<K> subSet(K fromElement, K toElement) {
      return new Maps$SortedKeySet<>(this.map().subMap(fromElement, toElement));
   }

   public SortedSet<K> headSet(K toElement) {
      return new Maps$SortedKeySet<>(this.map().headMap(toElement));
   }

   public SortedSet<K> tailSet(K fromElement) {
      return new Maps$SortedKeySet<>(this.map().tailMap(fromElement));
   }

    K first() {
      return this.map().firstKey();
   }

    K last() {
      return this.map().lastKey();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
