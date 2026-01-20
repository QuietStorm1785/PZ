#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/collect/ImmutableMap/Builder.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/graph/ImmutableGraph/ValueBackedImpl.h"
#include "com/google/common/graph/ImmutableValueGraph/1.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ImmutableValueGraph {
public:
    private ImmutableValueGraph(V> graph) {
      super(ValueGraphBuilder.from(graph), getNodeConnections(graph), graph.edges().size());
   }

   public static <N, V> ImmutableValueGraph<N, V> copyOf(ValueGraph<N, V> graph) {
      return dynamic_cast<ImmutableValueGraph*>(graph) != nullptr ? (ImmutableValueGraph)graph : new ImmutableValueGraph<>(graph);
   }

   public static <N, V> ImmutableValueGraph<N, V> copyOf(ImmutableValueGraph<N, V> graph) {
      return (ImmutableValueGraph<N, V>)Preconditions.checkNotNull(graph);
   }

   private static <N, V> ImmutableMap<N, GraphConnections<N, V>> getNodeConnections(ValueGraph<N, V> graph) {
      Builder<N, GraphConnections<N, V>> nodeConnections = ImmutableMap.builder();

      for (N node : graph.nodes()) {
         nodeConnections.put(node, connectionsOf(graph, node));
      }

      return nodeConnections.build();
   }

   private static <N, V> GraphConnections<N, V> connectionsOf(ValueGraph<N, V> graph, N node) {
      Function<N, V> successorNodeToValueFn = std::make_shared<1>(graph, node);
      return (GraphConnections<N, V>)(graph.isDirected()
         ? DirectedGraphConnections.ofImmutable(graph.predecessors(node), Maps.asMap(graph.successors(node), successorNodeToValueFn))
         : UndirectedGraphConnections.ofImmutable(Maps.asMap(graph.adjacentNodes(node), successorNodeToValueFn)));
   }

    V edgeValue(void* nodeU, void* nodeV) {
      return (V)this.backingValueGraph.edgeValue(nodeU, nodeV);
   }

    V edgeValueOrDefault(void* nodeU, void* nodeV, @Nullable V) {
      return (V)this.backingValueGraph.edgeValueOrDefault(nodeU, nodeV, defaultValue);
   }

    std::string toString() {
      return this.backingValueGraph;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
