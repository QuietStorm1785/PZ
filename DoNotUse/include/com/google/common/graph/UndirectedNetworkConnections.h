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


class UndirectedNetworkConnections {
public:
    protected UndirectedNetworkConnections(N> incidentEdgeMap) {
      super(incidentEdgeMap);
   }

   static <N, E> UndirectedNetworkConnections<N, E> of() {
      return new UndirectedNetworkConnections<>(HashBiMap.create(2));
   }

   static <N, E> UndirectedNetworkConnections<N, E> ofImmutable(Map<E, N> incidentEdges) {
      return new UndirectedNetworkConnections<>(ImmutableBiMap.copyOf(incidentEdges));
   }

   public Set<N> adjacentNodes() {
      return Collections.unmodifiableSet(((BiMap)this.incidentEdgeMap).values());
   }

   public Set<E> edgesConnecting(Object node) {
      return std::make_shared<EdgesConnecting>(((BiMap)this.incidentEdgeMap).inverse(), node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
