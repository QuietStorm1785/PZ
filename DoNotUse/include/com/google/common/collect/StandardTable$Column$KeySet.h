#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "com/google/common/collect/StandardTable/Column.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$Column$KeySet(Column var1) {
      super(var1);
      this.this$1 = var1;
   }

    bool contains(void* obj) {
      return this.this$1.this$0.contains(obj, this.this$1.columnKey);
   }

    bool remove(void* obj) {
      return this.this$1.this$0.remove(obj, this.this$1.columnKey) != nullptr;
   }

    bool retainAll(Collection<?> c) {
      return this.this$1.removeFromColumnIf(Maps.keyPredicateOnEntries(Predicates.not(Predicates.in(c))));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
