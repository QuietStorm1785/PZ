#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/KeySet.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   TreeRangeMap$SubRangeMap$SubRangeMapAsMap$1(SubRangeMapAsMap var1, Map x0) {
      super(x0);
      this.this$2 = var1;
   }

    bool remove(@Nullable Object) {
      return this.this$2.remove(o) != nullptr;
   }

    bool retainAll(Collection<?> c) {
      return SubRangeMapAsMap.access$300(this.this$2, Predicates.compose(Predicates.not(Predicates.in(c)), Maps.keyFunction()));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
