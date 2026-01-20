#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/DenseImmutableTable/ImmutableArrayMap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class DenseImmutableTable {
public:
    const int rowIndex;

   DenseImmutableTable$Row(DenseImmutableTable var1, int rowIndex) {
      super(DenseImmutableTable.access$200(var1)[rowIndex]);
      this.this$0 = var1;
      this.rowIndex = rowIndex;
   }

   ImmutableMap<C, int> keyToIndex() {
      return DenseImmutableTable.access$300(this.this$0);
   }

    V getValue(int keyIndex) {
      return (V)DenseImmutableTable.access$400(this.this$0)[this.rowIndex][keyIndex];
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
