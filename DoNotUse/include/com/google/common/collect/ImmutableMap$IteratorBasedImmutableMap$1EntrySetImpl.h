#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/IteratorBasedImmutableMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   ImmutableMap$IteratorBasedImmutableMap$1EntrySetImpl(IteratorBasedImmutableMap var1) {
      this.this$0 = var1;
   }

   ImmutableMap<K, V> map() {
      return this.this$0;
   }

   public UnmodifiableIterator<Entry<K, V>> iterator() {
      return this.this$0.entryIterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
