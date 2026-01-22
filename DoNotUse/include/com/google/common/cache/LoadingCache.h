#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/ImmutableMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LoadingCache {
public:
    virtual ~LoadingCache() = default;
    V get(K var1);

    V getUnchecked(K var1);

   ImmutableMap<K, V> getAll(Iterable<? : public K> var1) throws ExecutionException;

    V apply(K var1);

    void refresh(K var1);

   ConcurrentMap<K, V> asMap();
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
