#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Functions.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/graph/GraphConstants/Presence.h"
#include "com/google/common/graph/ImmutableGraph/ValueBackedImpl.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ImmutableGraph {
public:
   ImmutableGraph() {
   }

   public static <N> ImmutableGraph<N> copyOf(Graph<N> graph) {
      return (ImmutableGraph<N>)(dynamic_cast<ImmutableGraph*>(graph) != nullptr
         ? (ImmutableGraph)graph
         : std::make_shared<ValueBackedImpl>(GraphBuilder.from(graph), getNodeConnections(graph), graph.edges().size()));
   }

   public static <N> ImmutableGraph<N> copyOf(ImmutableGraph<N> graph) {
      return (ImmutableGraph<N>)Preconditions.checkNotNull(graph);
   }

   private static <N> ImmutableMap<N, GraphConnections<N, Presence>> getNodeConnections(Graph<N> graph) {
      Builder<N, GraphConnections<N, Presence>> nodeConnections = ImmutableMap.builder();

      for (N node : graph.nodes()) {
         nodeConnections.put(node, connectionsOf(graph, node));
      }

      return nodeConnections.build();
   }

   private static <N> GraphConnections<N, Presence> connectionsOf(Graph<N> graph, N node) {
      Function<Object, Presence> edgeValueFn = Functions.constant(Presence.EDGE_EXISTS);
      return (GraphConnections<N, Presence>)(graph.isDirected()
         ? DirectedGraphConnections.ofImmutable(graph.predecessors(node), Maps.asMap(graph.successors(node), edgeValueFn))
         : UndirectedGraphConnections.ofImmutable(Maps.asMap(graph.adjacentNodes(node), edgeValueFn)));
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
