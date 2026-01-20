#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMultimap {
public:
   ImmutableMultimap$Keys(ImmutableMultimap var1) {
      this.this$0 = var1;
   }

    bool contains(@Nullable Object) {
      return this.this$0.containsKey(object);
   }

    int count(@Nullable Object) {
      Collection<V> values = (Collection<V>)this.this$0.map.get(element);
    return values = = nullptr ? 0 : values.size();
   }

   public Set<K> elementSet() {
      return this.this$0.keySet();
   }

    int size() {
      return this.this$0.size();
   }

   com.google.common.collect.Multiset.Entry<K> getEntry(int index) {
      Entry<K, ? : public Collection<V>> entry = (Entry<K, ? : public Collection<V>>)this.this$0.map.entrySet().asList().get(index);
      return Multisets.immutableEntry(entry.getKey(), ((Collection)entry.getValue()).size());
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
