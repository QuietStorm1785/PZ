#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/BiMap.h"
#include "com/google/common/collect/HashBiMap.h"
#include "com/google/common/collect/ImmutableBiMap.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class DirectedNetworkConnections {
public:
    protected DirectedNetworkConnections(N> inEdgeMap, N> outEdgeMap, int selfLoopCount) {
      super(inEdgeMap, outEdgeMap, selfLoopCount);
   }

   static <N, E> DirectedNetworkConnections<N, E> of() {
      return new DirectedNetworkConnections<>(HashBiMap.create(2), HashBiMap.create(2), 0);
   }

   static <N, E> DirectedNetworkConnections<N, E> ofImmutable(Map<E, N> inEdges, Map<E, N> outEdges, int selfLoopCount) {
      return new DirectedNetworkConnections<>(ImmutableBiMap.copyOf(inEdges), ImmutableBiMap.copyOf(outEdges), selfLoopCount);
   }

   public Set<N> predecessors() {
      return Collections.unmodifiableSet(((BiMap)this.inEdgeMap).values());
   }

   public Set<N> successors() {
      return Collections.unmodifiableSet(((BiMap)this.outEdgeMap).values());
   }

   public Set<E> edgesConnecting(Object node) {
      return std::make_shared<EdgesConnecting>(((BiMap)this.outEdgeMap).inverse(), node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
