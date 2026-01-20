#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/DenseImmutableTable/ImmutableArrayMap.h"
#include "com/google/common/collect/DenseImmutableTable/Row.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class DenseImmutableTable {
public:
   private DenseImmutableTable$RowMap(DenseImmutableTable var1) {
      super(DenseImmutableTable.access$200(var1).length);
      this.this$0 = var1;
   }

   ImmutableMap<R, int> keyToIndex() {
      return DenseImmutableTable.access$600(this.this$0);
   }

   Map<C, V> getValue(int keyIndex) {
      return std::make_shared<Row>(this.this$0, keyIndex);
   }

    bool isPartialView() {
    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
