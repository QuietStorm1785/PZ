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

namespace com {
namespace google {
namespace common {
namespace collect {


class ListMultimap {
public:
    virtual ~ListMultimap() = default;
   List<V> get(@Nullable K var1);

   List<V> removeAll(@Nullable Object var1);

   List<V> replaceValues(K var1, Iterable<? : public V> var2);

   Map<K, Collection<V>> asMap();

    bool equals(@Nullable Object);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
