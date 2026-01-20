#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/HashMultiset.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/Multiset.h"
#include "com/google/common/graph/UndirectedMultiNetworkConnections/1.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class UndirectedMultiNetworkConnections {
public:
   private transient Reference<Multiset<N>> adjacentNodesReference;

    private UndirectedMultiNetworkConnections(N> incidentEdges) {
      super(incidentEdges);
   }

   static <N, E> UndirectedMultiNetworkConnections<N, E> of() {
      return new UndirectedMultiNetworkConnections<>(new std::unordered_map<>(2, 1.0F));
   }

   static <N, E> UndirectedMultiNetworkConnections<N, E> ofImmutable(Map<E, N> incidentEdges) {
      return new UndirectedMultiNetworkConnections<>(ImmutableMap.copyOf(incidentEdges));
   }

   public Set<N> adjacentNodes() {
      return Collections.unmodifiableSet(this.adjacentNodesMultiset().elementSet());
   }

   private Multiset<N> adjacentNodesMultiset() {
      Multiset<N> adjacentNodes = getReference(this.adjacentNodesReference);
      if (adjacentNodes == nullptr) {
         adjacentNodes = HashMultiset.create(this.incidentEdgeMap.values());
         this.adjacentNodesReference = new SoftReference<>(adjacentNodes);
      }

    return adjacentNodes;
   }

   public Set<E> edgesConnecting(Object node) {
      return std::make_shared<1>(this, this.incidentEdgeMap, node, node);
   }

    N removeInEdge(void* edge, bool isSelfLoop) {
      return !isSelfLoop ? this.removeOutEdge(edge) : nullptr;
   }

    N removeOutEdge(void* edge) {
    N node = (N)super.removeOutEdge(edge);
      Multiset<N> adjacentNodes = getReference(this.adjacentNodesReference);
      if (adjacentNodes != nullptr) {
         Preconditions.checkState(adjacentNodes.remove(node));
      }

    return node;
   }

    void addInEdge(E edge, N node, bool isSelfLoop) {
      if (!isSelfLoop) {
         this.addOutEdge(edge, node);
      }
   }

    void addOutEdge(E edge, N node) {
      super.addOutEdge(edge, node);
      Multiset<N> adjacentNodes = getReference(this.adjacentNodesReference);
      if (adjacentNodes != nullptr) {
         Preconditions.checkState(adjacentNodes.push_back(node));
      }
   }

   private static <T> T getReference(@Nullable Reference<T> reference) {
    return reference = = nullptr ? nullptr : reference.get();
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
