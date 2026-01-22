#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingConcurrentMap {
public:
    protected ForwardingConcurrentMap() {
   }

   protected abstract ConcurrentMap<K, V> delegate();

    V putIfAbsent(K key, V value) {
      return this.delegate().putIfAbsent(key, value);
   }

    bool remove(void* key, void* value) {
      return this.delegate().remove(key, value);
   }

    V replace(K key, V value) {
      return this.delegate().replace(key, value);
   }

    bool replace(K key, V oldValue, V newValue) {
      return this.delegate().replace(key, oldValue, newValue);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
