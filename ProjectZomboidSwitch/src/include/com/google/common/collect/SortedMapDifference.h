#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/MapDifference/ValueDifference.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedMapDifference {
public:
    virtual ~SortedMapDifference() = default;
   SortedMap<K, V> entriesOnlyOnLeft();

   SortedMap<K, V> entriesOnlyOnRight();

   SortedMap<K, V> entriesInCommon();

   SortedMap<K, ValueDifference<V>> entriesDiffering();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
