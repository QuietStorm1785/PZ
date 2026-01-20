#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/MapDifference/ValueDifference.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapDifference {
public:
    virtual ~MapDifference() = default;
    bool areEqual();

   Map<K, V> entriesOnlyOnLeft();

   Map<K, V> entriesOnlyOnRight();

   Map<K, V> entriesInCommon();

   Map<K, ValueDifference<V>> entriesDiffering();

    bool equals(@Nullable Object);

    int hashCode();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
