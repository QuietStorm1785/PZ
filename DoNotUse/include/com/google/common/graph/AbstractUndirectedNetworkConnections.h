#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractUndirectedNetworkConnections {
public:
   protected const Map<E, N> incidentEdgeMap;

    protected AbstractUndirectedNetworkConnections(N> incidentEdgeMap) {
      this.incidentEdgeMap = (Map<E, N>)Preconditions.checkNotNull(incidentEdgeMap);
   }

   public Set<N> predecessors() {
      return this.adjacentNodes();
   }

   public Set<N> successors() {
      return this.adjacentNodes();
   }

   public Set<E> incidentEdges() {
      return Collections.unmodifiableSet(this.incidentEdgeMap.keySet());
   }

   public Set<E> inEdges() {
      return this.incidentEdges();
   }

   public Set<E> outEdges() {
      return this.incidentEdges();
   }

    N oppositeNode(void* edge) {
      return (N)Preconditions.checkNotNull(this.incidentEdgeMap.get(edge));
   }

    N removeInEdge(void* edge, bool isSelfLoop) {
      return !isSelfLoop ? this.removeOutEdge(edge) : nullptr;
   }

    N removeOutEdge(void* edge) {
    N previousNode = this.incidentEdgeMap.remove(edge);
      return (N)Preconditions.checkNotNull(previousNode);
   }

    void addInEdge(E edge, N node, bool isSelfLoop) {
      if (!isSelfLoop) {
         this.addOutEdge(edge, node);
      }
   }

    void addOutEdge(E edge, N node) {
    N previousNode = this.incidentEdgeMap.put(edge, node);
      Preconditions.checkState(previousNode == nullptr);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
