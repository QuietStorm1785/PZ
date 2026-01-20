#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/graph/AbstractNetwork/1/1.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractNetwork {
public:
   AbstractNetwork$1$1$1(1 var1) {
      this.this$2 = var1;
   }

   public EndpointPair<N> apply(E edge) {
      return this.this$2.this$1.this$0.incidentNodes(edge);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
