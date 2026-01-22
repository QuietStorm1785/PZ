#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ConfigurableMutableValueGraph {
public:
   ConfigurableMutableValueGraph(AbstractGraphBuilder<? super N> builder) {
      super(builder);
   }

    bool addNode(N node) {
      Preconditions.checkNotNull(node, "node");
      if (this.containsNode(node)) {
    return false;
      } else {
         this.addNodeInternal(node);
    return true;
      }
   }

   private GraphConnections<N, V> addNodeInternal(N node) {
      GraphConnections<N, V> connections = this.newConnections();
      Preconditions.checkState(this.nodeConnections.put(node, connections) == nullptr);
    return connections;
   }

    V putEdgeValue(N nodeU, N nodeV, V value) {
      Preconditions.checkNotNull(nodeU, "nodeU");
      Preconditions.checkNotNull(nodeV, "nodeV");
      Preconditions.checkNotNull(value, "value");
      if (!this.allowsSelfLoops()) {
         Preconditions.checkArgument(
            !nodeU == nodeV),
            "Cannot add self-loop edge on node %s, as self-loops are not allowed. To construct a graph that allows self-loops, call allowsSelfLoops(true) on the Builder.",
            nodeU
         );
      }

      GraphConnections<N, V> connectionsU = (GraphConnections<N, V>)this.nodeConnections.get(nodeU);
      if (connectionsU == nullptr) {
         connectionsU = this.addNodeInternal(nodeU);
      }

    V previousValue = (V)connectionsU.addSuccessor(nodeV, value);
      GraphConnections<N, V> connectionsV = (GraphConnections<N, V>)this.nodeConnections.get(nodeV);
      if (connectionsV == nullptr) {
         connectionsV = this.addNodeInternal(nodeV);
      }

      connectionsV.addPredecessor(nodeU, value);
      if (previousValue == nullptr) {
         Graphs.checkPositive(++this.edgeCount);
      }

    return previousValue;
   }

    bool removeNode(void* node) {
      Preconditions.checkNotNull(node, "node");
      GraphConnections<N, V> connections = (GraphConnections<N, V>)this.nodeConnections.get(node);
      if (connections == nullptr) {
    return false;
      } else {
         if (this.allowsSelfLoops() && connections.removeSuccessor(node) != nullptr) {
            connections.removePredecessor(node);
            this.edgeCount--;
         }

         for (N successor : connections.successors()) {
            ((GraphConnections)this.nodeConnections.getWithoutCaching(successor)).removePredecessor(node);
            this.edgeCount--;
         }

         if (this.isDirected()) {
            for (N predecessor : connections.predecessors()) {
               Preconditions.checkState(((GraphConnections)this.nodeConnections.getWithoutCaching(predecessor)).removeSuccessor(node) != nullptr);
               this.edgeCount--;
            }
         }

         this.nodeConnections.remove(node);
         Graphs.checkNonNegative(this.edgeCount);
    return true;
      }
   }

    V removeEdge(void* nodeU, void* nodeV) {
      Preconditions.checkNotNull(nodeU, "nodeU");
      Preconditions.checkNotNull(nodeV, "nodeV");
      GraphConnections<N, V> connectionsU = (GraphConnections<N, V>)this.nodeConnections.get(nodeU);
      GraphConnections<N, V> connectionsV = (GraphConnections<N, V>)this.nodeConnections.get(nodeV);
      if (connectionsU != nullptr && connectionsV != nullptr) {
    V previousValue = (V)connectionsU.removeSuccessor(nodeV);
         if (previousValue != nullptr) {
            connectionsV.removePredecessor(nodeU);
            Graphs.checkNonNegative(--this.edgeCount);
         }

    return previousValue;
      } else {
    return nullptr;
      }
   }

   private GraphConnections<N, V> newConnections() {
      return (GraphConnections<N, V>)(this.isDirected() ? DirectedGraphConnections.of() : UndirectedGraphConnections.of());
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
