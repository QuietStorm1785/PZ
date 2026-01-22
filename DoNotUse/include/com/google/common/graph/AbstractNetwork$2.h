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


class AbstractNetwork {
public:
   AbstractNetwork$2(AbstractNetwork var1) {
      this.this$0 = var1;
   }

   public EndpointPair<N> apply(E edge) {
      return this.this$0.incidentNodes(edge);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
