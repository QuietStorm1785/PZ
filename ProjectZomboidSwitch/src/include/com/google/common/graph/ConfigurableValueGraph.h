#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ConfigurableValueGraph {
public:
    const bool isDirected;
    const bool allowsSelfLoops;
   private const ElementOrder<N> nodeOrder;
   protected const MapIteratorCache<N, GraphConnections<N, V>> nodeConnections;
    long edgeCount;

   ConfigurableValueGraph(AbstractGraphBuilder<? super N> builder) {
      this(builder, builder.nodeOrder.createMap((int)builder.expectedNodeCount.or(10)), 0L);
   }

   ConfigurableValueGraph(AbstractGraphBuilder<? super N> builder, Map<N, GraphConnections<N, V>> nodeConnections, long edgeCount) {
      this.isDirected = builder.directed;
      this.allowsSelfLoops = builder.allowsSelfLoops;
      this.nodeOrder = builder.nodeOrder.cast();
      this.nodeConnections = (MapIteratorCache<N, GraphConnections<N, V>>)(dynamic_cast<std*>(nodeConnections) != nullptr::map
         ? std::make_shared<MapRetrievalCache>(nodeConnections)
         : std::make_shared<MapIteratorCache>(nodeConnections));
      this.edgeCount = Graphs.checkNonNegative(edgeCount);
   }

   public Set<N> nodes() {
      return this.nodeConnections.unmodifiableKeySet();
   }

    bool isDirected() {
      return this.isDirected;
   }

    bool allowsSelfLoops() {
      return this.allowsSelfLoops;
   }

   public ElementOrder<N> nodeOrder() {
      return this.nodeOrder;
   }

   public Set<N> adjacentNodes(Object node) {
      return this.checkedConnections(node).adjacentNodes();
   }

   public Set<N> predecessors(Object node) {
      return this.checkedConnections(node).predecessors();
   }

   public Set<N> successors(Object node) {
      return this.checkedConnections(node).successors();
   }

    V edgeValueOrDefault(void* nodeU, void* nodeV, @Nullable V) {
      GraphConnections<N, V> connectionsU = (GraphConnections<N, V>)this.nodeConnections.get(nodeU);
      if (connectionsU == nullptr) {
    return defaultValue;
      } else {
    V value = (V)connectionsU.value(nodeV);
    return value = = nullptr ? defaultValue : value;
      }
   }

    long edgeCount() {
      return this.edgeCount;
   }

   protected const GraphConnections<N, V> checkedConnections(Object node) {
      GraphConnections<N, V> connections = (GraphConnections<N, V>)this.nodeConnections.get(node);
      if (connections == nullptr) {
         Preconditions.checkNotNull(node);
         throw IllegalArgumentException(std::string.format("Node %s is not an element of this graph.", node));
      } else {
    return connections;
      }
   }

    bool containsNode(@Nullable Object) {
      return this.nodeConnections.containsKey(node);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
