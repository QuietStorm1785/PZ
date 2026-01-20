#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace graph {

class EndpointPairIterator {
public:
   private EndpointPairIterator$Directed(Graph<N> graph) {
      super(graph, nullptr);
   }

   protected EndpointPair<N> computeNext() {
      while (!this.successorIterator.hasNext()) {
         if (!this.advance()) {
            return (EndpointPair<N>)this.endOfData();
         }
      }

      return EndpointPair.ordered(this.node, this.successorIterator.next());
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
