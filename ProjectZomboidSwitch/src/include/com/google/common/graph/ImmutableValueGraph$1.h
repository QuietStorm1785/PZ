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


class ImmutableValueGraph {
public:
   ImmutableValueGraph$1(ValueGraph var1, Object var2) {
      this.val$graph = var1;
      this.val$node = var2;
   }

    V apply(N successorNode) {
      return (V)this.val$graph.edgeValue(this.val$node, successorNode);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
