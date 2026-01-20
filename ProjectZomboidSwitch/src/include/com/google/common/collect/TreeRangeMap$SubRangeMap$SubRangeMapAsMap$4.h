#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicates.h"
#include "com/google/common/collect/Maps/Values.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   TreeRangeMap$SubRangeMap$SubRangeMapAsMap$4(SubRangeMapAsMap var1, Map x0) {
      super(x0);
      this.this$2 = var1;
   }

    bool removeAll(Collection<?> c) {
      return SubRangeMapAsMap.access$300(this.this$2, Predicates.compose(Predicates.in(c), Maps.valueFunction()));
   }

    bool retainAll(Collection<?> c) {
      return SubRangeMapAsMap.access$300(this.this$2, Predicates.compose(Predicates.not(Predicates.in(c)), Maps.valueFunction()));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
