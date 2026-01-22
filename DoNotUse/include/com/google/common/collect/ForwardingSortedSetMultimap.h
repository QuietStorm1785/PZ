#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingSortedSetMultimap {
public:
    protected ForwardingSortedSetMultimap() {
   }

   protected abstract SortedSetMultimap<K, V> delegate();

   public SortedSet<V> get(@Nullable K key) {
      return this.delegate().get(key);
   }

   public SortedSet<V> removeAll(@Nullable Object key) {
      return this.delegate().removeAll(key);
   }

   public SortedSet<V> replaceValues(K key, Iterable<? : public V> values) {
      return this.delegate().replaceValues(key, values);
   }

   public Comparator<? super V> valueComparator() {
      return this.delegate().valueComparator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
