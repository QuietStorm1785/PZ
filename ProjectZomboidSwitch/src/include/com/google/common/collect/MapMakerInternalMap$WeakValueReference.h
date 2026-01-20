#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
    virtual ~MapMakerInternalMap() = default;
    V get();

    E getEntry();

    void clear();

   MapMakerInternalMap$WeakValueReference<K, V, E> copyFor(ReferenceQueue<V> var1, E var2);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
