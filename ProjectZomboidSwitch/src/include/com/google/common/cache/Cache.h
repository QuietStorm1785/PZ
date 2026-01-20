#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class Cache {
public:
    virtual ~Cache() = default;
    V getIfPresent(void* var1);

    V get(K var1, Callable<? extends);

   ImmutableMap<K, V> getAllPresent(Iterable<?> var1);

    void put(K var1, V var2);

    void putAll(Map<? extends, ? extends);

    void invalidate(void* var1);

    void invalidateAll(Iterable<?> var1);

    void invalidateAll();

    long size();

    CacheStats stats();

   ConcurrentMap<K, V> asMap();

    void cleanUp();
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
