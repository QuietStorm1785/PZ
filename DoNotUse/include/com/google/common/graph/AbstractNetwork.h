#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/Sets.h"
#include "com/google/common/graph/AbstractNetwork/1.h"
#include "com/google/common/graph/AbstractNetwork/2.h"
#include "com/google/common/math/IntMath.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractNetwork {
public:
   public Graph<N> asGraph() {
      return std::make_shared<1>(this);
   }

    int degree(void* node) {
      return this.isDirected()
         ? IntMath.saturatedAdd(this.inEdges(node).size(), this.outEdges(node).size())
         : IntMath.saturatedAdd(this.incidentEdges(node).size(), this.edgesConnecting(node, node).size());
   }

    int inDegree(void* node) {
      return this.isDirected() ? this.inEdges(node).size() : this.degree(node);
   }

    int outDegree(void* node) {
      return this.isDirected() ? this.outEdges(node).size() : this.degree(node);
   }

   public Set<E> adjacentEdges(Object edge) {
      EndpointPair<?> endpointPair = this.incidentNodes(edge);
      Set<E> endpointPairIncidentEdges = Sets.union(this.incidentEdges(endpointPair.nodeU()), this.incidentEdges(endpointPair.nodeV()));
      return Sets.difference(endpointPairIncidentEdges, ImmutableSet.of(edge));
   }

    std::string toString() {
      std::string propertiesString = std::string.format(
         "isDirected: %s, allowsParallelEdges: %s, allowsSelfLoops: %s", this.isDirected(), this.allowsParallelEdges(), this.allowsSelfLoops()
      );
      return std::string.format("%s, nodes: %s, edges: %s", propertiesString, this.nodes(), this.edgeIncidentNodesMap());
   }

   private Map<E, EndpointPair<N>> edgeIncidentNodesMap() {
      Function<E, EndpointPair<N>> edgeToIncidentNodesFn = std::make_shared<2>(this);
      return Maps.asMap(this.edges(), edgeToIncidentNodesFn);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
