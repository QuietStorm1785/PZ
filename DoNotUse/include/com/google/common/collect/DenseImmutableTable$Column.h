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
    const int columnIndex;

   DenseImmutableTable$Column(DenseImmutableTable var1, int columnIndex) {
      super(DenseImmutableTable.access$500(var1)[columnIndex]);
      this.this$0 = var1;
      this.columnIndex = columnIndex;
   }

   ImmutableMap<R, int> keyToIndex() {
      return DenseImmutableTable.access$600(this.this$0);
   }

    V getValue(int keyIndex) {
      return (V)DenseImmutableTable.access$400(this.this$0)[keyIndex][this.columnIndex];
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
