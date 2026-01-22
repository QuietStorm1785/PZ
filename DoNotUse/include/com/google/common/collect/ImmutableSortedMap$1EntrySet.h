#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSortedMap/1EntrySet/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMap {
public:
   ImmutableSortedMap$1EntrySet(ImmutableSortedMap var1) {
      this.this$0 = var1;
   }

   public UnmodifiableIterator<Entry<K, V>> iterator() {
      return this.asList().iterator();
   }

   ImmutableList<Entry<K, V>> createAsList() {
      return std::make_shared<1>(this);
   }

   ImmutableMap<K, V> map() {
      return this.this$0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
