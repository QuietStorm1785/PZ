#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapDifference/ValueDifference.h"
#include "com/google/common/collect/Maps/MapDifferenceImpl.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$SortedMapDifferenceImpl(SortedMap<K, V> onlyOnLeft, SortedMap<K, V> onlyOnRight, SortedMap<K, V> onBoth, SortedMap<K, ValueDifference<V>> differences) {
      super(onlyOnLeft, onlyOnRight, onBoth, differences);
   }

   public SortedMap<K, ValueDifference<V>> entriesDiffering() {
      return (SortedMap<K, ValueDifference<V>>)super.entriesDiffering();
   }

   public SortedMap<K, V> entriesInCommon() {
      return (SortedMap<K, V>)super.entriesInCommon();
   }

   public SortedMap<K, V> entriesOnlyOnLeft() {
      return (SortedMap<K, V>)super.entriesOnlyOnLeft();
   }

   public SortedMap<K, V> entriesOnlyOnRight() {
      return (SortedMap<K, V>)super.entriesOnlyOnRight();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
