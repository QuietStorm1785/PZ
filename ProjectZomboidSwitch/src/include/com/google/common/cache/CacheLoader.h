#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/cache/CacheLoader/1.h"
#include "com/google/common/cache/CacheLoader/FunctionToCacheLoader.h"
#include "com/google/common/cache/CacheLoader/SupplierToCacheLoader.h"
#include "com/google/common/cache/CacheLoader/UnsupportedLoadingOperationException.h"
#include "com/google/common/util/concurrent/Futures.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheLoader {
public:
    protected CacheLoader() {
   }

   public abstract V load(K var1) throws Exception;

   public ListenableFuture<V> reload(K key, V oldValue) throws Exception {
      Preconditions.checkNotNull(key);
      Preconditions.checkNotNull(oldValue);
      return Futures.immediateFuture(this.load(key));
   }

   public Map<K, V> loadAll(Iterable<? : public K> keys) throws Exception {
      throw std::make_unique<UnsupportedLoadingOperationException>();
   }

   public static <K, V> CacheLoader<K, V> from(Function<K, V> function) {
      return std::make_shared<FunctionToCacheLoader>(function);
   }

   public static <V> CacheLoader<Object, V> from(Supplier<V> supplier) {
      return std::make_shared<SupplierToCacheLoader>(supplier);
   }

   public static <K, V> CacheLoader<K, V> asyncReloading(CacheLoader<K, V> loader, Executor executor) {
      Preconditions.checkNotNull(loader);
      Preconditions.checkNotNull(executor);
      return std::make_shared<1>(loader, executor);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
