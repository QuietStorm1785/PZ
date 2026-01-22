#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/RegularImmutableBiMap/Inverse/InverseEntrySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableBiMap {
public:
   RegularImmutableBiMap$Inverse$InverseEntrySet$1(InverseEntrySet var1) {
      this.this$2 = var1;
   }

   public Entry<V, K> get(int index) {
      Entry<K, V> entry = RegularImmutableBiMap.access$400(this.this$2.this$1.this$0)[index];
      return Maps.immutableEntry(entry.getValue(), entry.getKey());
   }

   ImmutableCollection<Entry<V, K>> delegateCollection() {
      return this.this$2;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
