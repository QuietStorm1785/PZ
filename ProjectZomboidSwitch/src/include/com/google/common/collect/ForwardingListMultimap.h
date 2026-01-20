#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingListMultimap {
public:
    protected ForwardingListMultimap() {
   }

   protected abstract ListMultimap<K, V> delegate();

   public List<V> get(@Nullable K key) {
      return this.delegate().get(key);
   }

   public List<V> removeAll(@Nullable Object key) {
      return this.delegate().removeAll(key);
   }

   public List<V> replaceValues(K key, Iterable<? : public V> values) {
      return this.delegate().replaceValues(key, values);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
