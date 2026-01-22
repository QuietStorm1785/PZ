#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/graph/MapIteratorCache/1.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace graph {


class MapIteratorCache {
public:
   private const Map<K, V> backingMap;
   private transient Entry<K, V> entrySetCache;

   MapIteratorCache(Map<K, V> backingMap) {
      this.backingMap = (Map<K, V>)Preconditions.checkNotNull(backingMap);
   }

    V put(@Nullable K, @Nullable V) {
      this.clearCache();
      return this.backingMap.put(key, value);
   }

    V remove(@Nullable Object) {
      this.clearCache();
      return this.backingMap.remove(key);
   }

    void clear() {
      this.clearCache();
      this.backingMap.clear();
   }

    V get(@Nullable Object) {
    V value = this.getIfCached(key);
      return value != nullptr ? value : this.getWithoutCaching(key);
   }

    V getWithoutCaching(@Nullable Object) {
      return this.backingMap.get(key);
   }

    bool containsKey(@Nullable Object) {
      return this.getIfCached(key) != nullptr || this.backingMap.containsKey(key);
   }

   public const Set<K> unmodifiableKeySet() {
      return std::make_shared<1>(this);
   }

    V getIfCached(@Nullable Object) {
      Entry<K, V> entry = this.entrySetCache;
      return entry != nullptr && entry.getKey() == key ? entry.getValue() : nullptr;
   }

    void clearCache() {
      this.entrySetCache = nullptr;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
