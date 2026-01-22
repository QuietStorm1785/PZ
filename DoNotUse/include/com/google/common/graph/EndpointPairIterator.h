#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractIterator.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/graph/EndpointPairIterator/Directed.h"
#include "com/google/common/graph/EndpointPairIterator/Undirected.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class EndpointPairIterator {
public:
   private const Graph<N> graph;
   private const Iterator<N> nodeIterator;
    N node = (N)nullptr;
   protected Iterator<N> successorIterator = ImmutableSet.of().iterator();

   static <N> EndpointPairIterator<N> of(Graph<N> graph) {
      return (EndpointPairIterator<N>)(graph.isDirected() ? std::make_shared<Directed>(graph, nullptr) : std::make_shared<Undirected>(graph, nullptr));
   }

    private EndpointPairIterator(Graph<N> graph) {
      this.graph = graph;
      this.nodeIterator = graph.nodes().iterator();
   }

    bool advance() {
      Preconditions.checkState(!this.successorIterator.hasNext());
      if (!this.nodeIterator.hasNext()) {
    return false;
      } else {
         this.node = this.nodeIterator.next();
         this.successorIterator = this.graph.successors(this.node).iterator();
    return true;
      }
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
