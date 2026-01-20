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
#include "com/google/common/graph/ImmutableNetwork/1.h"
#include "com/google/common/graph/ImmutableNetwork/2.h"
#include "com/google/common/graph/ImmutableNetwork/3.h"
#include "com/google/common/graph/ImmutableNetwork/4.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ImmutableNetwork {
public:
    private ImmutableNetwork(E> network) {
      super(NetworkBuilder.from(network), getNodeConnections(network), getEdgeToReferenceNode(network));
   }

   public static <N, E> ImmutableNetwork<N, E> copyOf(Network<N, E> network) {
      return dynamic_cast<ImmutableNetwork*>(network) != nullptr ? (ImmutableNetwork)network : new ImmutableNetwork<>(network);
   }

   public static <N, E> ImmutableNetwork<N, E> copyOf(ImmutableNetwork<N, E> network) {
      return (ImmutableNetwork<N, E>)Preconditions.checkNotNull(network);
   }

   public ImmutableGraph<N> asGraph() {
      Graph<N> asGraph = super.asGraph();
      return std::make_shared<1>(this, asGraph);
   }

   private static <N, E> Map<N, NetworkConnections<N, E>> getNodeConnections(Network<N, E> network) {
      Builder<N, NetworkConnections<N, E>> nodeConnections = ImmutableMap.builder();

      for (N node : network.nodes()) {
         nodeConnections.put(node, connectionsOf(network, node));
      }

      return nodeConnections.build();
   }

   private static <N, E> Map<E, N> getEdgeToReferenceNode(Network<N, E> network) {
      Builder<E, N> edgeToReferenceNode = ImmutableMap.builder();

      for (E edge : network.edges()) {
         edgeToReferenceNode.put(edge, network.incidentNodes(edge).nodeU());
      }

      return edgeToReferenceNode.build();
   }

   private static <N, E> NetworkConnections<N, E> connectionsOf(Network<N, E> network, N node) {
      if (network.isDirected()) {
         Map<E, N> inEdgeMap = Maps.asMap(network.inEdges(node), sourceNodeFn(network));
         Map<E, N> outEdgeMap = Maps.asMap(network.outEdges(node), targetNodeFn(network));
    int selfLoopCount = network.edgesConnecting(node, node).size();
         return (NetworkConnections<N, E>)(network.allowsParallelEdges()
            ? DirectedMultiNetworkConnections.ofImmutable(inEdgeMap, outEdgeMap, selfLoopCount)
            : DirectedNetworkConnections.ofImmutable(inEdgeMap, outEdgeMap, selfLoopCount));
      } else {
         Map<E, N> incidentEdgeMap = Maps.asMap(network.incidentEdges(node), adjacentNodeFn(network, node));
         return (NetworkConnections<N, E>)(network.allowsParallelEdges()
            ? UndirectedMultiNetworkConnections.ofImmutable(incidentEdgeMap)
            : UndirectedNetworkConnections.ofImmutable(incidentEdgeMap));
      }
   }

   private static <N, E> Function<E, N> sourceNodeFn(Network<N, E> network) {
      return std::make_shared<2>(network);
   }

   private static <N, E> Function<E, N> targetNodeFn(Network<N, E> network) {
      return std::make_shared<3>(network);
   }

   private static <N, E> Function<E, N> adjacentNodeFn(Network<N, E> network, N node) {
      return std::make_shared<4>(network, node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
