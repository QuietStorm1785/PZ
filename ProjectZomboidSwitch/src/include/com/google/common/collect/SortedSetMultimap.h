#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class SortedSetMultimap {
public:
    virtual ~SortedSetMultimap() = default;
   SortedSet<V> get(@Nullable K var1);

   SortedSet<V> removeAll(@Nullable Object var1);

   SortedSet<V> replaceValues(K var1, Iterable<? : public V> var2);

   Map<K, Collection<V>> asMap();

   Comparator<? super V> valueComparator();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
