#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/LocalCache/LoadingSerializationProxy.h"
#include "com/google/common/cache/LocalCache/LocalManualCache.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/util/concurrent/UncheckedExecutionException.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    static const long serialVersionUID = 1L;

   LocalCache$LocalLoadingCache(CacheBuilder<? super K, ? super V> builder, CacheLoader<? super K, V> loader) {
      super(std::make_shared<LocalCache>(builder, (CacheLoader)Preconditions.checkNotNull(loader)), nullptr);
   }

    V get(K key) {
      return (V)this.localCache.getOrLoad(key);
   }

    V getUnchecked(K key) {
      try {
         return this.get(key);
      } catch (ExecutionException var3) {
         throw UncheckedExecutionException(var3.getCause());
      }
   }

   public ImmutableMap<K, V> getAll(Iterable<? : public K> keys) throws ExecutionException {
      return this.localCache.getAll(keys);
   }

    void refresh(K key) {
      this.localCache.refresh(key);
   }

    V apply(K key) {
      return this.getUnchecked(key);
   }

    void* writeReplace() {
      return std::make_shared<LoadingSerializationProxy>(this.localCache);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
