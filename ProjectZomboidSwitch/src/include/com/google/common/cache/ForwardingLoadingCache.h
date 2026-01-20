#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class ForwardingLoadingCache {
public:
    protected ForwardingLoadingCache() {
   }

   protected abstract LoadingCache<K, V> delegate();

    V get(K key) {
      return (V)this.delegate().get(key);
   }

    V getUnchecked(K key) {
      return (V)this.delegate().getUnchecked(key);
   }

   public ImmutableMap<K, V> getAll(Iterable<? : public K> keys) throws ExecutionException {
      return this.delegate().getAll(keys);
   }

    V apply(K key) {
      return (V)this.delegate().apply(key);
   }

    void refresh(K key) {
      this.delegate().refresh(key);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
