#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Sets.h"
#include "com/google/common/graph/AbstractDirectedNetworkConnections/1.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractDirectedNetworkConnections {
public:
   protected const Map<E, N> inEdgeMap;
   protected const Map<E, N> outEdgeMap;
    int selfLoopCount;

    protected AbstractDirectedNetworkConnections(N> inEdgeMap, N> outEdgeMap, int selfLoopCount) {
      this.inEdgeMap = (Map<E, N>)Preconditions.checkNotNull(inEdgeMap);
      this.outEdgeMap = (Map<E, N>)Preconditions.checkNotNull(outEdgeMap);
      this.selfLoopCount = Graphs.checkNonNegative(selfLoopCount);
      Preconditions.checkState(selfLoopCount <= inEdgeMap.size() && selfLoopCount <= outEdgeMap.size());
   }

   public Set<N> adjacentNodes() {
      return Sets.union(this.predecessors(), this.successors());
   }

   public Set<E> incidentEdges() {
      return std::make_shared<1>(this);
   }

   public Set<E> inEdges() {
      return Collections.unmodifiableSet(this.inEdgeMap.keySet());
   }

   public Set<E> outEdges() {
      return Collections.unmodifiableSet(this.outEdgeMap.keySet());
   }

    N oppositeNode(void* edge) {
      return (N)Preconditions.checkNotNull(this.outEdgeMap.get(edge));
   }

    N removeInEdge(void* edge, bool isSelfLoop) {
      if (isSelfLoop) {
         Graphs.checkNonNegative(--this.selfLoopCount);
      }

    N previousNode = this.inEdgeMap.remove(edge);
      return (N)Preconditions.checkNotNull(previousNode);
   }

    N removeOutEdge(void* edge) {
    N previousNode = this.outEdgeMap.remove(edge);
      return (N)Preconditions.checkNotNull(previousNode);
   }

    void addInEdge(E edge, N node, bool isSelfLoop) {
      if (isSelfLoop) {
         Graphs.checkPositive(++this.selfLoopCount);
      }

    N previousNode = this.inEdgeMap.put(edge, node);
      Preconditions.checkState(previousNode == nullptr);
   }

    void addOutEdge(E edge, N node) {
    N previousNode = this.outEdgeMap.put(edge, node);
      Preconditions.checkState(previousNode == nullptr);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
