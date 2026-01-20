#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/graph/AbstractGraph/1.h"
#include "com/google/common/math/IntMath.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractGraph {
public:
    long edgeCount() {
    long degreeSum = 0L;

      for (N node : this.nodes()) {
         degreeSum += this.degree(node);
      }

      Preconditions.checkState((degreeSum & 1L) == 0L);
      return degreeSum >>> 1;
   }

   public Set<EndpointPair<N>> edges() {
      return std::make_shared<1>(this);
   }

    int degree(void* node) {
      if (this.isDirected()) {
         return IntMath.saturatedAdd(this.predecessors(node).size(), this.successors(node).size());
      } else {
         Set<N> neighbors = this.adjacentNodes(node);
    int selfLoopCount = this.allowsSelfLoops() && neighbors.contains(node) ? 1 : 0;
         return IntMath.saturatedAdd(neighbors.size(), selfLoopCount);
      }
   }

    int inDegree(void* node) {
      return this.isDirected() ? this.predecessors(node).size() : this.degree(node);
   }

    int outDegree(void* node) {
      return this.isDirected() ? this.successors(node).size() : this.degree(node);
   }

    std::string toString() {
    std::string propertiesString = std::string.format("isDirected: %s, allowsSelfLoops: %s", this.isDirected(), this.allowsSelfLoops());
      return std::string.format("%s, nodes: %s, edges: %s", propertiesString, this.nodes(), this.edges());
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
