#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Synchronized/SynchronizedSetMultimap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedSortedSetMultimap(SortedSetMultimap<K, V> delegate, @Nullable Object mutex) {
      super(delegate, mutex);
   }

   SortedSetMultimap<K, V> delegate() {
      return (SortedSetMultimap<K, V>)super.delegate();
   }

   public SortedSet<V> get(K key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return Synchronized.access$100(this.delegate().get(key), this.mutex);
      }
   }

   public SortedSet<V> removeAll(Object key) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().removeAll(key);
      }
   }

   public SortedSet<V> replaceValues(K key, Iterable<? : public V> values) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().replaceValues(key, values);
      }
   }

   public Comparator<? super V> valueComparator() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate().valueComparator();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
