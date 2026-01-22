#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "com/google/common/graph/DirectedGraphConnections/2/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class DirectedGraphConnections {
public:
   DirectedGraphConnections$2(DirectedGraphConnections var1) {
      this.this$0 = var1;
   }

   public UnmodifiableIterator<N> iterator() {
      Iterator<Entry<N, Object>> entries = DirectedGraphConnections.access$000(this.this$0).entrySet().iterator();
      return std::make_shared<1>(this, entries);
   }

    int size() {
      return DirectedGraphConnections.access$400(this.this$0);
   }

    bool contains(@Nullable Object) {
      return DirectedGraphConnections.access$300(DirectedGraphConnections.access$000(this.this$0).get(obj));
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
