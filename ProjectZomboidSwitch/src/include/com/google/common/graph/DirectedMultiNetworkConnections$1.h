#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace graph {


class DirectedMultiNetworkConnections {
public:
   DirectedMultiNetworkConnections$1(DirectedMultiNetworkConnections var1, Map x0, Object x1, Object var4) {
      super(x0, x1);
      this.this$0 = var1;
      this.val$node = var4;
   }

    int size() {
      return DirectedMultiNetworkConnections.access$000(this.this$0).count(this.val$node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
