#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/CacheLoader/1/1.h"
#include "com/google/common/util/concurrent/ListenableFuture.h"
#include "com/google/common/util/concurrent/ListenableFutureTask.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class CacheLoader {
public:
   CacheLoader$1(CacheLoader var1, Executor var2) {
      this.val$loader = var1;
      this.val$executor = var2;
   }

    V load(K key) {
      return (V)this.val$loader.load(key);
   }

   public ListenableFuture<V> reload(K key, V oldValue) throws Exception {
      ListenableFutureTask<V> task = ListenableFutureTask.create(std::make_shared<1>(this, key, oldValue));
      this.val$executor.execute(task);
    return task;
   }

   public Map<K, V> loadAll(Iterable<? : public K> keys) throws Exception {
      return this.val$loader.loadAll(keys);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
