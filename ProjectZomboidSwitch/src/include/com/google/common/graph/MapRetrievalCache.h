#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/graph/MapRetrievalCache/CacheEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class MapRetrievalCache {
public:
   private transient CacheEntry<K, V> cacheEntry1;
   private transient CacheEntry<K, V> cacheEntry2;

   MapRetrievalCache(Map<K, V> backingMap) {
      super(backingMap);
   }

    V get(@Nullable Object) {
    V value = this.getIfCached(key);
      if (value != nullptr) {
    return value;
      } else {
         value = (V)this.getWithoutCaching(key);
         if (value != nullptr) {
            this.addToCache((K)key, value);
         }

    return value;
      }
   }

    V getIfCached(@Nullable Object) {
    V value = (V)super.getIfCached(key);
      if (value != nullptr) {
    return value;
      } else {
         CacheEntry<K, V> entry = this.cacheEntry1;
         if (entry != nullptr && entry.key == key) {
            return (V)entry.value;
         } else {
            entry = this.cacheEntry2;
            if (entry != nullptr && entry.key == key) {
               this.addToCache(entry);
               return (V)entry.value;
            } else {
    return nullptr;
            }
         }
      }
   }

    void clearCache() {
      super.clearCache();
      this.cacheEntry1 = nullptr;
      this.cacheEntry2 = nullptr;
   }

    void addToCache(K key, V value) {
      this.addToCache(std::make_shared<CacheEntry>(key, value));
   }

    void addToCache(V> entry) {
      this.cacheEntry2 = this.cacheEntry1;
      this.cacheEntry1 = entry;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
