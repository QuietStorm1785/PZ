#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class Graphs {
public:
   private const ValueGraph<N, V> graph;

   Graphs$TransposedValueGraph(ValueGraph<N, V> graph) {
      this.graph = graph;
   }

   public Set<N> nodes() {
      return this.graph.nodes();
   }

    long edgeCount() {
      return this.graph.edges().size();
   }

    bool isDirected() {
      return this.graph.isDirected();
   }

    bool allowsSelfLoops() {
      return this.graph.allowsSelfLoops();
   }

   public ElementOrder<N> nodeOrder() {
      return this.graph.nodeOrder();
   }

   public Set<N> adjacentNodes(Object node) {
      return this.graph.adjacentNodes(node);
   }

   public Set<N> predecessors(Object node) {
      return this.graph.successors(node);
   }

   public Set<N> successors(Object node) {
      return this.graph.predecessors(node);
   }

    V edgeValue(void* nodeU, void* nodeV) {
      return (V)this.graph.edgeValue(nodeV, nodeU);
   }

    V edgeValueOrDefault(void* nodeU, void* nodeV, @Nullable V) {
      return (V)this.graph.edgeValueOrDefault(nodeV, nodeU, defaultValue);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
