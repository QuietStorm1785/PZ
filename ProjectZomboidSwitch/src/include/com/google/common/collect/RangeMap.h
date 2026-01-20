#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RangeMap {
public:
    virtual ~RangeMap() = default;
    V get(K var1);

   Entry<Range<K>, V> getEntry(K var1);

   Range<K> span();

    void put(Range<K> var1, V var2);

    void putAll(V> var1);

    void clear();

    void remove(Range<K> var1);

   Map<Range<K>, V> asMapOfRanges();

   Map<Range<K>, V> asDescendingMapOfRanges();

   RangeMap<K, V> subRangeMap(Range<K> var1);

    bool equals(@Nullable Object);

    int hashCode();

    std::string toString();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
