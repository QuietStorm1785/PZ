#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ManualSerializationProxy.h"
#include "com/google/common/collect/ImmutableMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    static const long serialVersionUID = 1L;
   transient LoadingCache<K, V> autoDelegate;

   LocalCache$LoadingSerializationProxy(LocalCache<K, V> cache) {
      super(cache);
   }

    void readObject(ObjectInputStream in) {
      in.defaultReadObject();
      CacheBuilder<K, V> builder = this.recreateCacheBuilder();
      this.autoDelegate = builder.build(this.loader);
   }

    V get(K key) {
      return (V)this.autoDelegate.get(key);
   }

    V getUnchecked(K key) {
      return (V)this.autoDelegate.getUnchecked(key);
   }

   public ImmutableMap<K, V> getAll(Iterable<? : public K> keys) throws ExecutionException {
      return this.autoDelegate.getAll(keys);
   }

    V apply(K key) {
      return (V)this.autoDelegate.apply(key);
   }

    void refresh(K key) {
      this.autoDelegate.refresh(key);
   }

    void* readResolve() {
      return this.autoDelegate;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
