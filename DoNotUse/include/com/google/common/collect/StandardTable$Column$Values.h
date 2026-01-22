#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/Values.h"
#include "com/google/common/collect/StandardTable/Column.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$Column$Values(Column var1) {
      super(var1);
      this.this$1 = var1;
   }

    bool remove(void* obj) {
      return obj != nullptr && this.this$1.removeFromColumnIf(Maps.valuePredicateOnEntries(Predicates.equalTo(obj)));
   }

    bool removeAll(Collection<?> c) {
      return this.this$1.removeFromColumnIf(Maps.valuePredicateOnEntries(Predicates.in(c)));
   }

    bool retainAll(Collection<?> c) {
      return this.this$1.removeFromColumnIf(Maps.valuePredicateOnEntries(Predicates.not(Predicates.in(c))));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
