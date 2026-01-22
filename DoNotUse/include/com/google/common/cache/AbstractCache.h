#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/Maps.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class AbstractCache {
public:
    protected AbstractCache() {
   }

    V get(K key, Callable<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableMap<K, V> getAllPresent(Iterable<?> keys) {
      Map<K, V> result = Maps.newLinkedHashMap();

    for (auto& key : keys)         if (!result.containsKey(key)) {
    V value = (V)this.getIfPresent(key);
            if (value != nullptr) {
               result.put((K)key, value);
            }
         }
      }

      return ImmutableMap.copyOf(result);
   }

    void put(K key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public K, ? : public V> entry : m.entrySet()) {
         this.put((K)entry.getKey(), (V)entry.getValue());
      }
   }

    void cleanUp() {
   }

    long size() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void invalidate(void* key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void invalidateAll(Iterable<?> keys) {
    for (auto& key : keys)         this.invalidate(key);
      }
   }

    void invalidateAll() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    CacheStats stats() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ConcurrentMap<K, V> asMap() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
