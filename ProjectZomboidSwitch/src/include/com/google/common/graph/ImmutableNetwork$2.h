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
   ImmutableNetwork$2(Network var1) {
      this.val$network = var1;
   }

    N apply(E edge) {
      return (N)this.val$network.incidentNodes(edge).source();
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
