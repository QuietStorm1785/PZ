#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ForwardingObject.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class ForwardingCache {
public:
    protected ForwardingCache() {
   }

   protected abstract Cache<K, V> delegate();

    V getIfPresent(void* key) {
      return (V)this.delegate().getIfPresent(key);
   }

    V get(K key, Callable<? extends) {
      return (V)this.delegate().get(key, valueLoader);
   }

   public ImmutableMap<K, V> getAllPresent(Iterable<?> keys) {
      return this.delegate().getAllPresent(keys);
   }

    void put(K key, V value) {
      this.delegate().put(key, value);
   }

    void putAll(Map<? extends, ? extends) {
      this.delegate().putAll(m);
   }

    void invalidate(void* key) {
      this.delegate().invalidate(key);
   }

    void invalidateAll(Iterable<?> keys) {
      this.delegate().invalidateAll(keys);
   }

    void invalidateAll() {
      this.delegate().invalidateAll();
   }

    long size() {
      return this.delegate().size();
   }

    CacheStats stats() {
      return this.delegate().stats();
   }

   public ConcurrentMap<K, V> asMap() {
      return this.delegate().asMap();
   }

    void cleanUp() {
      this.delegate().cleanUp();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
