#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractSortedKeySortedSetMultimap {
public:
   AbstractSortedKeySortedSetMultimap(SortedMap<K, Collection<V>> map) {
      super(map);
   }

   public SortedMap<K, Collection<V>> asMap() {
      return (SortedMap<K, Collection<V>>)super.asMap();
   }

   SortedMap<K, Collection<V>> backingMap() {
      return (SortedMap<K, Collection<V>>)super.backingMap();
   }

   public SortedSet<K> keySet() {
      return (SortedSet<K>)super.keySet();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
