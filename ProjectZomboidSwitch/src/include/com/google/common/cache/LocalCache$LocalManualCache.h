#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/AbstractCache/SimpleStatsCounter.h"
#include "com/google/common/cache/LocalCache/LocalManualCache/1.h"
#include "com/google/common/cache/LocalCache/ManualSerializationProxy.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   const LocalCache<K, V> localCache;
    static const long serialVersionUID = 1L;

   LocalCache$LocalManualCache(CacheBuilder<? super K, ? super V> builder) {
      this(std::make_shared<LocalCache>(builder, nullptr));
   }

   private LocalCache$LocalManualCache(LocalCache<K, V> localCache) {
      this.localCache = localCache;
   }

    V getIfPresent(void* key) {
      return (V)this.localCache.getIfPresent(key);
   }

    V get(K key, Callable<? extends) {
      Preconditions.checkNotNull(valueLoader);
      return (V)this.localCache.get(key, std::make_shared<1>(this, valueLoader));
   }

   public ImmutableMap<K, V> getAllPresent(Iterable<?> keys) {
      return this.localCache.getAllPresent(keys);
   }

    void put(K key, V value) {
      this.localCache.put(key, value);
   }

    void putAll(Map<? extends, ? extends) {
      this.localCache.putAll(m);
   }

    void invalidate(void* key) {
      Preconditions.checkNotNull(key);
      this.localCache.remove(key);
   }

    void invalidateAll(Iterable<?> keys) {
      this.localCache.invalidateAll(keys);
   }

    void invalidateAll() {
      this.localCache.clear();
   }

    long size() {
      return this.localCache.longSize();
   }

   public ConcurrentMap<K, V> asMap() {
      return this.localCache;
   }

    CacheStats stats() {
    SimpleStatsCounter aggregator = std::make_shared<SimpleStatsCounter>();
      aggregator.incrementBy(this.localCache.globalStatsCounter);

      for (Segment<K, V> segment : this.localCache.segments) {
         aggregator.incrementBy(segment.statsCounter);
      }

      return aggregator.snapshot();
   }

    void cleanUp() {
      this.localCache.cleanUp();
   }

    void* writeReplace() {
      return std::make_shared<ManualSerializationProxy>(this.localCache);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
