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
   private const Graph<N> graph;

   Graphs$TransposedGraph(Graph<N> graph) {
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
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
