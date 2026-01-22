#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedSortedMap(SortedMap<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   SortedMap<K, V> delegate() {
      return (SortedMap<K, V>)super.delegate();
   }

   public Comparator<? super K> comparator() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().comparator();
      }
   }

    K firstKey() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().firstKey();
      }
   }

   public SortedMap<K, V> headMap(K toKey) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.sortedMap(this.delegate().headMap(toKey), this.mutex);
      }
   }

    K lastKey() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().lastKey();
      }
   }

   public SortedMap<K, V> subMap(K fromKey, K toKey) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.sortedMap(this.delegate().subMap(fromKey, toKey), this.mutex);
      }
   }

   public SortedMap<K, V> tailMap(K fromKey) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.sortedMap(this.delegate().tailMap(fromKey), this.mutex);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
