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


class ForwardingGraph {
public:
   protected abstract Graph<N> delegate();

   public Set<N> nodes() {
      return this.delegate().nodes();
   }

   public Set<EndpointPair<N>> edges() {
      return this.delegate().edges();
   }

    bool isDirected() {
      return this.delegate().isDirected();
   }

    bool allowsSelfLoops() {
      return this.delegate().allowsSelfLoops();
   }

   public ElementOrder<N> nodeOrder() {
      return this.delegate().nodeOrder();
   }

   public Set<N> adjacentNodes(Object node) {
      return this.delegate().adjacentNodes(node);
   }

   public Set<N> predecessors(Object node) {
      return this.delegate().predecessors(node);
   }

   public Set<N> successors(Object node) {
      return this.delegate().successors(node);
   }

    int degree(void* node) {
      return this.delegate().degree(node);
   }

    int inDegree(void* node) {
      return this.delegate().inDegree(node);
   }

    int outDegree(void* node) {
      return this.delegate().outDegree(node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
