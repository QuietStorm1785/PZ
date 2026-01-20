#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/MapViewOfValuesAsSingletonSets/1.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   ImmutableMap$MapViewOfValuesAsSingletonSets$1$1(1 var1, Entry var2) {
      this.this$2 = var1;
      this.val$backingEntry = var2;
   }

    K getKey() {
      return (K)this.val$backingEntry.getKey();
   }

   public ImmutableSet<V> getValue() {
      return ImmutableSet.of(this.val$backingEntry.getValue());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
