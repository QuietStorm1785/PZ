#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Iterables.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/graph/Graphs/NodeVisitState.h"
#include "com/google/common/graph/Graphs/TransposedGraph.h"
#include "com/google/common/graph/Graphs/TransposedNetwork.h"
#include "com/google/common/graph/Graphs/TransposedValueGraph.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace graph {


class Graphs {
public:
    private Graphs() {
   }

    static bool hasCycle(Graph<?> graph) {
    int numEdges = graph.edges().size();
      if (numEdges == 0) {
    return false;
      } else if (!graph.isDirected() && numEdges >= graph.nodes().size()) {
    return true;
      } else {
         Map<Object, NodeVisitState> visitedNodes = Maps.newHashMapWithExpectedSize(graph.nodes().size());

         for (Object node : graph.nodes()) {
            if (subgraphHasCycle(graph, visitedNodes, node, nullptr)) {
    return true;
            }
         }

    return false;
      }
   }

    static bool hasCycle(?> network) {
      return !network.isDirected() && network.allowsParallelEdges() && network.edges().size() > network.asGraph().edges().size()
         ? true
         : hasCycle(network.asGraph());
   }

    static bool subgraphHasCycle(Graph<?> graph, NodeVisitState> visitedNodes, void* node, @Nullable Object) {
    NodeVisitState state = visitedNodes.get(node);
      if (state == NodeVisitState.COMPLETE) {
    return false;
      } else if (state == NodeVisitState.PENDING) {
    return true;
      } else {
         visitedNodes.put(node, NodeVisitState.PENDING);

         for (Object nextNode : graph.successors(node)) {
            if (canTraverseWithoutReusingEdge(graph, nextNode, previousNode) && subgraphHasCycle(graph, visitedNodes, nextNode, node)) {
    return true;
            }
         }

         visitedNodes.put(node, NodeVisitState.COMPLETE);
    return false;
      }
   }

    static bool canTraverseWithoutReusingEdge(Graph<?> graph, void* nextNode, @Nullable Object) {
      return graph.isDirected() || !Objects.equal(previousNode, nextNode);
   }

   public static <N> Graph<N> transitiveClosure(Graph<N> graph) {
      MutableGraph<N> transitiveClosure = GraphBuilder.from(graph).allowsSelfLoops(true).build();
      if (graph.isDirected()) {
         for (N node : graph.nodes()) {
            for (N reachableNode : reachableNodes(graph, node)) {
               transitiveClosure.putEdge(node, reachableNode);
            }
         }
      } else {
         Set<N> visitedNodes = std::make_unique<std::unordered_set<>>();

         for (N node : graph.nodes()) {
            if (!visitedNodes.contains(node)) {
               Set<N> reachableNodes = reachableNodes(graph, node);
               visitedNodes.addAll(reachableNodes);
    int pairwiseMatch = 1;

    for (auto& nodeU : reachableNodes)                  for (N nodeV : Iterables.limit(reachableNodes, pairwiseMatch++)) {
                     transitiveClosure.putEdge(nodeU, nodeV);
                  }
               }
            }
         }
      }

    return transitiveClosure;
   }

   public static <N> Set<N> reachableNodes(Graph<N> graph, Object node) {
      Preconditions.checkArgument(graph.nodes().contains(node), "Node %s is not an element of this graph.", node);
      Set<N> visitedNodes = std::make_unique<LinkedHashSet<>>();
      std::queue<N> queuedNodes = std::make_unique<ArrayDeque<>>();
      visitedNodes.push_back((N)node);
      queuedNodes.push_back((N)node);

      while (!queuedNodes.empty()) {
    N currentNode = queuedNodes.remove();

         for (N successor : graph.successors(currentNode)) {
            if (visitedNodes.push_back(successor)) {
               queuedNodes.push_back(successor);
            }
         }
      }

      return Collections.unmodifiableSet(visitedNodes);
   }

    static bool equivalent(@Nullable Graph<?>, @Nullable Graph<?>) {
      if (graphA == graphB) {
    return true;
      } else {
         return graphA != nullptr && graphB != nullptr
            ? graphA.isDirected() == graphB.isDirected() && graphA.nodes() == graphB.nodes()) && graphA.edges() == graphB.edges())
            : false;
      }
   }

    static bool equivalent(@Nullable ValueGraph<?, ?> graphA, @Nullable ValueGraph<?, ?> graphB) {
      if (graphA == graphB) {
    return true;
      } else if (graphA != nullptr && graphB != nullptr) {
         if (graphA.isDirected() == graphB.isDirected() && graphA.nodes() == graphB.nodes()) && graphA.edges() == graphB.edges())) {
            for (EndpointPair<?> edge : graphA.edges()) {
               if (!graphA.edgeValue(edge.nodeU(), edge.nodeV()) == graphB.edgeValue(edge.nodeU(), edge.nodeV()))) {
    return false;
               }
            }

    return true;
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    static bool equivalent(@Nullable Network<?, ?> networkA, @Nullable Network<?, ?> networkB) {
      if (networkA == networkB) {
    return true;
      } else if (networkA != nullptr && networkB != nullptr) {
         if (networkA.isDirected() == networkB.isDirected() && networkA.nodes() == networkB.nodes()) && networkA.edges() == networkB.edges())) {
            for (Object edge : networkA.edges()) {
               if (!networkA.incidentNodes(edge) == networkB.incidentNodes(edge))) {
    return false;
               }
            }

    return true;
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

   public static <N> Graph<N> transpose(Graph<N> graph) {
      if (!graph.isDirected()) {
    return graph;
      } else {
         return (Graph<N>)(dynamic_cast<TransposedGraph*>(graph) != nullptr ? TransposedGraph.access$000((TransposedGraph)graph) : std::make_shared<TransposedGraph>(graph));
      }
   }

   public static <N, V> ValueGraph<N, V> transpose(ValueGraph<N, V> graph) {
      if (!graph.isDirected()) {
    return graph;
      } else {
         return (ValueGraph<N, V>)(dynamic_cast<TransposedValueGraph*>(graph) != nullptr
            ? TransposedValueGraph.access$100((TransposedValueGraph)graph)
            : std::make_shared<TransposedValueGraph>(graph));
      }
   }

   public static <N, E> Network<N, E> transpose(Network<N, E> network) {
      if (!network.isDirected()) {
    return network;
      } else {
         return (Network<N, E>)(dynamic_cast<TransposedNetwork*>(network) != nullptr
            ? TransposedNetwork.access$200((TransposedNetwork)network)
            : std::make_shared<TransposedNetwork>(network));
      }
   }

   public static <N> MutableGraph<N> inducedSubgraph(Graph<N> graph, Iterable<? : public N> nodes) {
      MutableGraph<N> subgraph = GraphBuilder.from(graph).build();

    for (auto& node : nodes)         subgraph.addNode(node);
      }

      for (N node : subgraph.nodes()) {
         for (N successorNode : graph.successors(node)) {
            if (subgraph.nodes().contains(successorNode)) {
               subgraph.putEdge(node, successorNode);
            }
         }
      }

    return subgraph;
   }

   public static <N, V> MutableValueGraph<N, V> inducedSubgraph(ValueGraph<N, V> graph, Iterable<? : public N> nodes) {
      MutableValueGraph<N, V> subgraph = ValueGraphBuilder.from(graph).build();

    for (auto& node : nodes)         subgraph.addNode(node);
      }

      for (N node : subgraph.nodes()) {
         for (N successorNode : graph.successors(node)) {
            if (subgraph.nodes().contains(successorNode)) {
               subgraph.putEdgeValue(node, successorNode, graph.edgeValue(node, successorNode));
            }
         }
      }

    return subgraph;
   }

   public static <N, E> MutableNetwork<N, E> inducedSubgraph(Network<N, E> network, Iterable<? : public N> nodes) {
      MutableNetwork<N, E> subgraph = NetworkBuilder.from(network).build();

    for (auto& node : nodes)         subgraph.addNode(node);
      }

      for (N node : subgraph.nodes()) {
         for (E edge : network.outEdges(node)) {
    N successorNode = (N)network.incidentNodes(edge).adjacentNode(node);
            if (subgraph.nodes().contains(successorNode)) {
               subgraph.addEdge(node, successorNode, edge);
            }
         }
      }

    return subgraph;
   }

   public static <N> MutableGraph<N> copyOf(Graph<N> graph) {
      MutableGraph<N> copy = GraphBuilder.from(graph).expectedNodeCount(graph.nodes().size()).build();

      for (N node : graph.nodes()) {
         copy.addNode(node);
      }

      for (EndpointPair<N> edge : graph.edges()) {
         copy.putEdge(edge.nodeU(), edge.nodeV());
      }

    return copy;
   }

   public static <N, V> MutableValueGraph<N, V> copyOf(ValueGraph<N, V> graph) {
      MutableValueGraph<N, V> copy = ValueGraphBuilder.from(graph).expectedNodeCount(graph.nodes().size()).build();

      for (N node : graph.nodes()) {
         copy.addNode(node);
      }

      for (EndpointPair<N> edge : graph.edges()) {
         copy.putEdgeValue(edge.nodeU(), edge.nodeV(), graph.edgeValue(edge.nodeU(), edge.nodeV()));
      }

    return copy;
   }

   public static <N, E> MutableNetwork<N, E> copyOf(Network<N, E> network) {
      MutableNetwork<N, E> copy = NetworkBuilder.from(network).expectedNodeCount(network.nodes().size()).expectedEdgeCount(network.edges().size()).build();

      for (N node : network.nodes()) {
         copy.addNode(node);
      }

      for (E edge : network.edges()) {
         EndpointPair<N> endpointPair = network.incidentNodes(edge);
         copy.addEdge(endpointPair.nodeU(), endpointPair.nodeV(), edge);
      }

    return copy;
   }

    static int checkNonNegative(int value) {
      Preconditions.checkArgument(value >= 0, "Not true that %s is non-negative.", value);
    return value;
   }

    static int checkPositive(int value) {
      Preconditions.checkArgument(value > 0, "Not true that %s is positive.", value);
    return value;
   }

    static long checkNonNegative(long value) {
      Preconditions.checkArgument(value >= 0L, "Not true that %s is non-negative.", value);
    return value;
   }

    static long checkPositive(long value) {
      Preconditions.checkArgument(value > 0L, "Not true that %s is positive.", value);
    return value;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
