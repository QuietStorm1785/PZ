#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractIterator.h"
#include "com/google/common/graph/DirectedGraphConnections/2.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class DirectedGraphConnections {
public:
   DirectedGraphConnections$2$1(2 var1, Iterator var2) {
      this.this$1 = var1;
      this.val$entries = var2;
   }

    N computeNext() {
      while (this.val$entries.hasNext()) {
         Entry<N, Object> entry = (Entry<N, Object>)this.val$entries.next();
         if (DirectedGraphConnections.access$300(entry.getValue())) {
            return (N)entry.getKey();
         }
      }

      return (N)this.endOfData();
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
