#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/graph/GraphConstants/Presence.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ConfigurableMutableGraph {
public:
   private const MutableValueGraph<N, Presence> backingValueGraph;

   ConfigurableMutableGraph(AbstractGraphBuilder<? super N> builder) {
      this.backingValueGraph = std::make_shared<ConfigurableMutableValueGraph>(builder);
   }

   protected Graph<N> delegate() {
      return this.backingValueGraph;
   }

    bool addNode(N node) {
      return this.backingValueGraph.addNode(node);
   }

    bool putEdge(N nodeU, N nodeV) {
      return this.backingValueGraph.putEdgeValue(nodeU, nodeV, Presence.EDGE_EXISTS) == nullptr;
   }

    bool removeNode(void* node) {
      return this.backingValueGraph.removeNode(node);
   }

    bool removeEdge(void* nodeU, void* nodeV) {
      return this.backingValueGraph.removeEdge(nodeU, nodeV) != nullptr;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
