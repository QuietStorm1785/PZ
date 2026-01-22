#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ConfigurableMutableNetwork {
public:
   ConfigurableMutableNetwork(NetworkBuilder<? super N, ? super E> builder) {
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

   private NetworkConnections<N, E> addNodeInternal(N node) {
      NetworkConnections<N, E> connections = this.newConnections();
      Preconditions.checkState(this.nodeConnections.put(node, connections) == nullptr);
    return connections;
   }

    bool addEdge(N nodeU, N nodeV, E edge) {
      Preconditions.checkNotNull(nodeU, "nodeU");
      Preconditions.checkNotNull(nodeV, "nodeV");
      Preconditions.checkNotNull(edge, "edge");
      if (this.containsEdge(edge)) {
         EndpointPair<N> existingIncidentNodes = this.incidentNodes(edge);
         EndpointPair<N> newIncidentNodes = EndpointPair.of(this, nodeU, nodeV);
         Preconditions.checkArgument(
            existingIncidentNodes == newIncidentNodes),
            "Edge %s already exists between the following nodes: %s, so it cannot be reused to connect the following nodes: %s.",
            edge,
            existingIncidentNodes,
            newIncidentNodes
         );
    return false;
      } else {
         NetworkConnections<N, E> connectionsU = (NetworkConnections<N, E>)this.nodeConnections.get(nodeU);
         if (!this.allowsParallelEdges()) {
            Preconditions.checkArgument(
               connectionsU == nullptr || !connectionsU.successors().contains(nodeV),
               "Nodes %s and %s are already connected by a different edge. To construct a graph that allows parallel edges, call allowsParallelEdges(true) on the Builder.",
               nodeU,
               nodeV
            );
         }

    bool isSelfLoop = nodeU == nodeV);
         if (!this.allowsSelfLoops()) {
            Preconditions.checkArgument(
               !isSelfLoop,
               "Cannot add self-loop edge on node %s, as self-loops are not allowed. To construct a graph that allows self-loops, call allowsSelfLoops(true) on the Builder.",
               nodeU
            );
         }

         if (connectionsU == nullptr) {
            connectionsU = this.addNodeInternal(nodeU);
         }

         connectionsU.addOutEdge(edge, nodeV);
         NetworkConnections<N, E> connectionsV = (NetworkConnections<N, E>)this.nodeConnections.get(nodeV);
         if (connectionsV == nullptr) {
            connectionsV = this.addNodeInternal(nodeV);
         }

         connectionsV.addInEdge(edge, nodeU, isSelfLoop);
         this.edgeToReferenceNode.put(edge, nodeU);
    return true;
      }
   }

    bool removeNode(void* node) {
      Preconditions.checkNotNull(node, "node");
      NetworkConnections<N, E> connections = (NetworkConnections<N, E>)this.nodeConnections.get(node);
      if (connections == nullptr) {
    return false;
      } else {
         for (E edge : ImmutableList.copyOf(connections.incidentEdges())) {
            this.removeEdge(edge);
         }

         this.nodeConnections.remove(node);
    return true;
      }
   }

    bool removeEdge(void* edge) {
      Preconditions.checkNotNull(edge, "edge");
    N nodeU = (N)this.edgeToReferenceNode.get(edge);
      if (nodeU == nullptr) {
    return false;
      } else {
         NetworkConnections<N, E> connectionsU = (NetworkConnections<N, E>)this.nodeConnections.get(nodeU);
    N nodeV = (N)connectionsU.oppositeNode(edge);
         NetworkConnections<N, E> connectionsV = (NetworkConnections<N, E>)this.nodeConnections.get(nodeV);
         connectionsU.removeOutEdge(edge);
         connectionsV.removeInEdge(edge, this.allowsSelfLoops() && nodeU == nodeV));
         this.edgeToReferenceNode.remove(edge);
    return true;
      }
   }

   private NetworkConnections<N, E> newConnections() {
      return (NetworkConnections<N, E>)(this.isDirected()
         ? (this.allowsParallelEdges() ? DirectedMultiNetworkConnections.of() : DirectedNetworkConnections.of())
         : (this.allowsParallelEdges() ? UndirectedMultiNetworkConnections.of() : UndirectedNetworkConnections.of()));
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
