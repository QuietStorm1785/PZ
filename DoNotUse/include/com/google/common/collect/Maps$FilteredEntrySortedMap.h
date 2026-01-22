#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Maps/FilteredEntryMap.h"
#include "com/google/common/collect/Maps/FilteredEntrySortedMap/SortedKeySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$FilteredEntrySortedMap(SortedMap<K, V> unfiltered, Predicate<? super Entry<K, V>> entryPredicate) {
      super(unfiltered, entryPredicate);
   }

   SortedMap<K, V> sortedMap() {
      return (SortedMap<K, V>)this.unfiltered;
   }

   public SortedSet<K> keySet() {
      return (SortedSet<K>)super.keySet();
   }

   SortedSet<K> createKeySet() {
      return std::make_shared<SortedKeySet>(this);
   }

   public Comparator<? super K> comparator() {
      return this.sortedMap().comparator();
   }

    K firstKey() {
      return this.keySet().iterator().next();
   }

    K lastKey() {
      SortedMap<K, V> headMap = this.sortedMap();

      while (true) {
    K key = headMap.lastKey();
         if (this.apply(key, this.unfiltered.get(key))) {
    return key;
         }

         headMap = this.sortedMap().headMap(key);
      }
   }

   public SortedMap<K, V> headMap(K toKey) {
      return new Maps$FilteredEntrySortedMap<>(this.sortedMap().headMap(toKey), this.predicate);
   }

   public SortedMap<K, V> subMap(K fromKey, K toKey) {
      return new Maps$FilteredEntrySortedMap<>(this.sortedMap().subMap(fromKey, toKey), this.predicate);
   }

   public SortedMap<K, V> tailMap(K fromKey) {
      return new Maps$FilteredEntrySortedMap<>(this.sortedMap().tailMap(fromKey), this.predicate);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
