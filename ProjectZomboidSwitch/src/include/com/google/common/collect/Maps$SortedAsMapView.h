#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/Maps/AsMapView.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$SortedAsMapView(SortedSet<K> set, Function<? super K, V> function) {
      super(set, function);
   }

   SortedSet<K> backingSet() {
      return (SortedSet<K>)super.backingSet();
   }

   public Comparator<? super K> comparator() {
      return this.backingSet().comparator();
   }

   public Set<K> keySet() {
      return Maps.access$300(this.backingSet());
   }

   public SortedMap<K, V> subMap(K fromKey, K toKey) {
      return Maps.asMap(this.backingSet().subSet(fromKey, toKey), this.function);
   }

   public SortedMap<K, V> headMap(K toKey) {
      return Maps.asMap(this.backingSet().headSet(toKey), this.function);
   }

   public SortedMap<K, V> tailMap(K fromKey) {
      return Maps.asMap(this.backingSet().tailSet(fromKey), this.function);
   }

    K firstKey() {
      return this.backingSet().first();
   }

    K lastKey() {
      return this.backingSet().last();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
