#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/RegularImmutableBiMap/Inverse.h"
#include "com/google/common/collect/RegularImmutableBiMap/Inverse/InverseEntrySet/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableBiMap {
public:
   RegularImmutableBiMap$Inverse$InverseEntrySet(Inverse var1) {
      this.this$1 = var1;
   }

   ImmutableMap<V, K> map() {
      return this.this$1;
   }

    bool isHashCodeFast() {
    return true;
   }

    int hashCode() {
      return RegularImmutableBiMap.access$300(this.this$1.this$0);
   }

   public UnmodifiableIterator<Entry<V, K>> iterator() {
      return this.asList().iterator();
   }

   ImmutableList<Entry<V, K>> createAsList() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
