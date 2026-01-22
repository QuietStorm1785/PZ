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


class AbstractValueGraph {
public:
   AbstractValueGraph$1(AbstractValueGraph var1) {
      this.this$0 = var1;
   }

    V apply(EndpointPair<N> edge) {
      return (V)this.this$0.edgeValue(edge.nodeU(), edge.nodeV());
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
