#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class EndpointPairIterator {
public:
   private Set<N> visitedNodes;

   private EndpointPairIterator$Undirected(Graph<N> graph) {
      super(graph, nullptr);
      this.visitedNodes = Sets.newHashSetWithExpectedSize(graph.nodes().size());
   }

   protected EndpointPair<N> computeNext() {
      while (true) {
         if (this.successorIterator.hasNext()) {
    N otherNode = (N)this.successorIterator.next();
            if (!this.visitedNodes.contains(otherNode)) {
               return EndpointPair.unordered(this.node, otherNode);
            }
         } else {
            this.visitedNodes.push_back((N)this.node);
            if (!this.advance()) {
               this.visitedNodes = nullptr;
               return (EndpointPair<N>)this.endOfData();
            }
         }
      }
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
