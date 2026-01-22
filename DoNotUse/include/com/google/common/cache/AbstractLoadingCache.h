#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/util/concurrent/UncheckedExecutionException.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace cache {


class AbstractLoadingCache {
public:
    protected AbstractLoadingCache() {
   }

    V getUnchecked(K key) {
      try {
         return (V)this.get(key);
      } catch (ExecutionException var3) {
         throw UncheckedExecutionException(var3.getCause());
      }
   }

   public ImmutableMap<K, V> getAll(Iterable<? : public K> keys) throws ExecutionException {
      Map<K, V> result = Maps.newLinkedHashMap();

    for (auto& key : keys)         if (!result.containsKey(key)) {
            result.put(key, (V)this.get(key));
         }
      }

      return ImmutableMap.copyOf(result);
   }

    V apply(K key) {
      return this.getUnchecked(key);
   }

    void refresh(K key) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
