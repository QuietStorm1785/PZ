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
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingSetMultimap {
public:
   protected abstract SetMultimap<K, V> delegate();

   public Set<Entry<K, V>> entries() {
      return this.delegate().entries();
   }

   public Set<V> get(@Nullable K key) {
      return this.delegate().get(key);
   }

   public Set<V> removeAll(@Nullable Object key) {
      return this.delegate().removeAll(key);
   }

   public Set<V> replaceValues(K key, Iterable<? : public V> values) {
      return this.delegate().replaceValues(key, values);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
