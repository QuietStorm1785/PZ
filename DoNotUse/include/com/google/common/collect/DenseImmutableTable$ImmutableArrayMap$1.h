#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/DenseImmutableTable/ImmutableArrayMap.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class DenseImmutableTable {
public:
    int index;
    const int maxIndex;

   DenseImmutableTable$ImmutableArrayMap$1(ImmutableArrayMap var1) {
      this.this$0 = var1;
      this.index = -1;
      this.maxIndex = this.this$0.keyToIndex().size();
   }

   protected Entry<K, V> computeNext() {
      this.index++;

      while (this.index < this.maxIndex) {
    V value = (V)this.this$0.getValue(this.index);
         if (value != nullptr) {
            return Maps.immutableEntry(this.this$0.getKey(this.index), value);
         }

         this.index++;
      }

      return (Entry<K, V>)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
