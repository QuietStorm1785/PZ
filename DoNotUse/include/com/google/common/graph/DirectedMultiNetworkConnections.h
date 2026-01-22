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
#include "com/google/common/graph/DirectedMultiNetworkConnections/1.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class DirectedMultiNetworkConnections {
public:
   private transient Reference<Multiset<N>> predecessorsReference;
   private transient Reference<Multiset<N>> successorsReference;

    private DirectedMultiNetworkConnections(N> inEdges, N> outEdges, int selfLoopCount) {
      super(inEdges, outEdges, selfLoopCount);
   }

   static <N, E> DirectedMultiNetworkConnections<N, E> of() {
      return new DirectedMultiNetworkConnections<>(new std::unordered_map<>(2, 1.0F), new std::unordered_map<>(2, 1.0F), 0);
   }

   static <N, E> DirectedMultiNetworkConnections<N, E> ofImmutable(Map<E, N> inEdges, Map<E, N> outEdges, int selfLoopCount) {
      return new DirectedMultiNetworkConnections<>(ImmutableMap.copyOf(inEdges), ImmutableMap.copyOf(outEdges), selfLoopCount);
   }

   public Set<N> predecessors() {
      return Collections.unmodifiableSet(this.predecessorsMultiset().elementSet());
   }

   private Multiset<N> predecessorsMultiset() {
      Multiset<N> predecessors = getReference(this.predecessorsReference);
      if (predecessors == nullptr) {
         predecessors = HashMultiset.create(this.inEdgeMap.values());
         this.predecessorsReference = new SoftReference<>(predecessors);
      }

    return predecessors;
   }

   public Set<N> successors() {
      return Collections.unmodifiableSet(this.successorsMultiset().elementSet());
   }

   private Multiset<N> successorsMultiset() {
      Multiset<N> successors = getReference(this.successorsReference);
      if (successors == nullptr) {
         successors = HashMultiset.create(this.outEdgeMap.values());
         this.successorsReference = new SoftReference<>(successors);
      }

    return successors;
   }

   public Set<E> edgesConnecting(Object node) {
      return std::make_shared<1>(this, this.outEdgeMap, node, node);
   }

    N removeInEdge(void* edge, bool isSelfLoop) {
    N node = (N)super.removeInEdge(edge, isSelfLoop);
      Multiset<N> predecessors = getReference(this.predecessorsReference);
      if (predecessors != nullptr) {
         Preconditions.checkState(predecessors.remove(node));
      }

    return node;
   }

    N removeOutEdge(void* edge) {
    N node = (N)super.removeOutEdge(edge);
      Multiset<N> successors = getReference(this.successorsReference);
      if (successors != nullptr) {
         Preconditions.checkState(successors.remove(node));
      }

    return node;
   }

    void addInEdge(E edge, N node, bool isSelfLoop) {
      super.addInEdge(edge, node, isSelfLoop);
      Multiset<N> predecessors = getReference(this.predecessorsReference);
      if (predecessors != nullptr) {
         Preconditions.checkState(predecessors.push_back(node));
      }
   }

    void addOutEdge(E edge, N node) {
      super.addOutEdge(edge, node);
      Multiset<N> successors = getReference(this.successorsReference);
      if (successors != nullptr) {
         Preconditions.checkState(successors.push_back(node));
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
