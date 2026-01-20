#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace graph {


class Graphs {
public:
   private const Network<N, E> network;

   Graphs$TransposedNetwork(Network<N, E> network) {
      this.network = network;
   }

   public Set<N> nodes() {
      return this.network.nodes();
   }

   public Set<E> edges() {
      return this.network.edges();
   }

    bool isDirected() {
      return this.network.isDirected();
   }

    bool allowsParallelEdges() {
      return this.network.allowsParallelEdges();
   }

    bool allowsSelfLoops() {
      return this.network.allowsSelfLoops();
   }

   public ElementOrder<N> nodeOrder() {
      return this.network.nodeOrder();
   }

   public ElementOrder<E> edgeOrder() {
      return this.network.edgeOrder();
   }

   public Set<N> adjacentNodes(Object node) {
      return this.network.adjacentNodes(node);
   }

   public Set<N> predecessors(Object node) {
      return this.network.successors(node);
   }

   public Set<N> successors(Object node) {
      return this.network.predecessors(node);
   }

   public Set<E> incidentEdges(Object node) {
      return this.network.incidentEdges(node);
   }

   public Set<E> inEdges(Object node) {
      return this.network.outEdges(node);
   }

   public Set<E> outEdges(Object node) {
      return this.network.inEdges(node);
   }

   public EndpointPair<N> incidentNodes(Object edge) {
      EndpointPair<N> endpointPair = this.network.incidentNodes(edge);
      return EndpointPair.of(this.network, endpointPair.nodeV(), endpointPair.nodeU());
   }

   public Set<E> adjacentEdges(Object edge) {
      return this.network.adjacentEdges(edge);
   }

   public Set<E> edgesConnecting(Object nodeU, Object nodeV) {
      return this.network.edgesConnecting(nodeV, nodeU);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
