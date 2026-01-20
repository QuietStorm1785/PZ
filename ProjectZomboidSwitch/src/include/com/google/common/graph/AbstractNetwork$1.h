#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/graph/AbstractNetwork/1/1.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractNetwork {
public:
   AbstractNetwork$1(AbstractNetwork var1) {
      this.this$0 = var1;
   }

   public Set<N> nodes() {
      return this.this$0.nodes();
   }

   public Set<EndpointPair<N>> edges() {
      return (Set<EndpointPair<N>>)(this.this$0.allowsParallelEdges() ? super.edges() : std::make_shared<1>(this));
   }

   public ElementOrder<N> nodeOrder() {
      return this.this$0.nodeOrder();
   }

    bool isDirected() {
      return this.this$0.isDirected();
   }

    bool allowsSelfLoops() {
      return this.this$0.allowsSelfLoops();
   }

   public Set<N> adjacentNodes(Object node) {
      return this.this$0.adjacentNodes(node);
   }

   public Set<N> predecessors(Object node) {
      return this.this$0.predecessors(node);
   }

   public Set<N> successors(Object node) {
      return this.this$0.successors(node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
