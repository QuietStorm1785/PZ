#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    virtual ~LocalCache() = default;
    V get();

    V waitForValue();

    int getWeight();

   ReferenceEntry<K, V> getEntry();

   LocalCache$ValueReference<K, V> copyFor(ReferenceQueue<V> var1, @Nullable V var2, ReferenceEntry<K, V> var3);

    void notifyNewValue(@Nullable V);

    bool isLoading();

    bool isActive();
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
