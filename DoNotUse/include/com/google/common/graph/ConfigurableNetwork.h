#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ConfigurableNetwork {
public:
    const bool isDirected;
    const bool allowsParallelEdges;
    const bool allowsSelfLoops;
   private const ElementOrder<N> nodeOrder;
   private const ElementOrder<E> edgeOrder;
   protected const MapIteratorCache<N, NetworkConnections<N, E>> nodeConnections;
   protected const MapIteratorCache<E, N> edgeToReferenceNode;

   ConfigurableNetwork(NetworkBuilder<? super N, ? super E> builder) {
      this(
         builder,
         builder.nodeOrder.createMap((int)builder.expectedNodeCount.or(10)),
         builder.edgeOrder.createMap((int)builder.expectedEdgeCount.or(20))
      );
   }

   ConfigurableNetwork(NetworkBuilder<? super N, ? super E> builder, Map<N, NetworkConnections<N, E>> nodeConnections, Map<E, N> edgeToReferenceNode) {
      this.isDirected = builder.directed;
      this.allowsParallelEdges = builder.allowsParallelEdges;
      this.allowsSelfLoops = builder.allowsSelfLoops;
      this.nodeOrder = builder.nodeOrder.cast();
      this.edgeOrder = builder.edgeOrder.cast();
      this.nodeConnections = (MapIteratorCache<N, NetworkConnections<N, E>>)(dynamic_cast<std*>(nodeConnections) != nullptr::map
         ? std::make_shared<MapRetrievalCache>(nodeConnections)
         : std::make_shared<MapIteratorCache>(nodeConnections));
      this.edgeToReferenceNode = std::make_shared<MapIteratorCache>(edgeToReferenceNode);
   }

   public Set<N> nodes() {
      return this.nodeConnections.unmodifiableKeySet();
   }

   public Set<E> edges() {
      return this.edgeToReferenceNode.unmodifiableKeySet();
   }

    bool isDirected() {
      return this.isDirected;
   }

    bool allowsParallelEdges() {
      return this.allowsParallelEdges;
   }

    bool allowsSelfLoops() {
      return this.allowsSelfLoops;
   }

   public ElementOrder<N> nodeOrder() {
      return this.nodeOrder;
   }

   public ElementOrder<E> edgeOrder() {
      return this.edgeOrder;
   }

   public Set<E> incidentEdges(Object node) {
      return this.checkedConnections(node).incidentEdges();
   }

   public EndpointPair<N> incidentNodes(Object edge) {
    N nodeU = this.checkedReferenceNode(edge);
    N nodeV = (N)((NetworkConnections)this.nodeConnections.get(nodeU)).oppositeNode(edge);
      return EndpointPair.of(this, nodeU, nodeV);
   }

   public Set<N> adjacentNodes(Object node) {
      return this.checkedConnections(node).adjacentNodes();
   }

   public Set<E> edgesConnecting(Object nodeU, Object nodeV) {
      NetworkConnections<N, E> connectionsU = this.checkedConnections(nodeU);
      if (!this.allowsSelfLoops && nodeU == nodeV) {
         return ImmutableSet.of();
      } else {
         Preconditions.checkArgument(this.containsNode(nodeV), "Node %s is not an element of this graph.", nodeV);
         return connectionsU.edgesConnecting(nodeV);
      }
   }

   public Set<E> inEdges(Object node) {
      return this.checkedConnections(node).inEdges();
   }

   public Set<E> outEdges(Object node) {
      return this.checkedConnections(node).outEdges();
   }

   public Set<N> predecessors(Object node) {
      return this.checkedConnections(node).predecessors();
   }

   public Set<N> successors(Object node) {
      return this.checkedConnections(node).successors();
   }

   protected const NetworkConnections<N, E> checkedConnections(Object node) {
      NetworkConnections<N, E> connections = (NetworkConnections<N, E>)this.nodeConnections.get(node);
      if (connections == nullptr) {
         Preconditions.checkNotNull(node);
         throw IllegalArgumentException(std::string.format("Node %s is not an element of this graph.", node));
      } else {
    return connections;
      }
   }

    N checkedReferenceNode(void* edge) {
    N referenceNode = (N)this.edgeToReferenceNode.get(edge);
      if (referenceNode == nullptr) {
         Preconditions.checkNotNull(edge);
         throw IllegalArgumentException(std::string.format("Edge %s is not an element of this graph.", edge));
      } else {
    return referenceNode;
      }
   }

    bool containsNode(@Nullable Object) {
      return this.nodeConnections.containsKey(node);
   }

    bool containsEdge(@Nullable Object) {
      return this.edgeToReferenceNode.containsKey(edge);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
