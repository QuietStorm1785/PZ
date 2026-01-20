#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Optional.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractGraphBuilder {
public:
    const bool directed;
    bool allowsSelfLoops = false;
   ElementOrder<N> nodeOrder = ElementOrder.insertion();
   Optional<int> expectedNodeCount = Optional.absent();

   AbstractGraphBuilder(boolean directed) {
      this.directed = directed;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
