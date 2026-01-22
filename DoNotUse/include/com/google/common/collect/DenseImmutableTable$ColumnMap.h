#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/DenseImmutableTable/Column.h"
#include "com/google/common/collect/DenseImmutableTable/ImmutableArrayMap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class DenseImmutableTable {
public:
   private DenseImmutableTable$ColumnMap(DenseImmutableTable var1) {
      super(DenseImmutableTable.access$500(var1).length);
      this.this$0 = var1;
   }

   ImmutableMap<C, int> keyToIndex() {
      return DenseImmutableTable.access$300(this.this$0);
   }

   Map<R, V> getValue(int keyIndex) {
      return std::make_shared<Column>(this.this$0, keyIndex);
   }

    bool isPartialView() {
    return false;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
