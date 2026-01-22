#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ImmutableNetwork {
public:
   ImmutableNetwork$4(Network var1, Object var2) {
      this.val$network = var1;
      this.val$node = var2;
   }

    N apply(E edge) {
      return (N)this.val$network.incidentNodes(edge).adjacentNode(this.val$node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
