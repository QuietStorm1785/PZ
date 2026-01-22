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


class SetMultimap {
public:
    virtual ~SetMultimap() = default;
   Set<V> get(@Nullable K var1);

   Set<V> removeAll(@Nullable Object var1);

   Set<V> replaceValues(K var1, Iterable<? : public V> var2);

   Set<Entry<K, V>> entries();

   Map<K, Collection<V>> asMap();

    bool equals(@Nullable Object);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
