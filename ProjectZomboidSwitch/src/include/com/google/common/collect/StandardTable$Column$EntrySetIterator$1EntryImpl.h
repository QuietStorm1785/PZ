#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/StandardTable/Column/EntrySetIterator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$Column$EntrySetIterator$1EntryImpl(EntrySetIterator var1, Entry var2) {
      this.this$2 = var1;
      this.val$entry = var2;
   }

    R getKey() {
      return (R)this.val$entry.getKey();
   }

    V getValue() {
      return (V)((Map)this.val$entry.getValue()).get(this.this$2.this$1.columnKey);
   }

    V setValue(V value) {
      return (V)((Map)this.val$entry.getValue()).put(this.this$2.this$1.columnKey, Preconditions.checkNotNull(value));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
