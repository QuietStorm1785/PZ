#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ImmutableGraph {
public:
   protected const ValueGraph<N, V> backingValueGraph;

   ImmutableGraph$ValueBackedImpl(AbstractGraphBuilder<? super N> builder, ImmutableMap<N, GraphConnections<N, V>> nodeConnections, long edgeCount) {
      this.backingValueGraph = std::make_shared<ConfigurableValueGraph>(builder, nodeConnections, edgeCount);
   }

   protected Graph<N> delegate() {
      return this.backingValueGraph;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
