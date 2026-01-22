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

class GraphConstants {
public:
    static const int EXPECTED_DEGREE = 2;
    static const int DEFAULT_NODE_COUNT = 10;
    static const int DEFAULT_EDGE_COUNT = 20;
    static const float INNER_LOAD_FACTOR = 1.0F;
    static const int INNER_CAPACITY = 2;
    static const std::string NODE_NOT_IN_GRAPH = "Node %s is not an element of this graph.";
    static const std::string EDGE_NOT_IN_GRAPH = "Edge %s is not an element of this graph.";
    static const std::string EDGE_CONNECTING_NOT_IN_GRAPH = "Edge connecting %s to %s is not present in this graph.";
    static const std::string REUSING_EDGE = "Edge %s already exists between the following nodes: %s, so it cannot be reused to connect the following nodes: %s.";
    static const std::string PARALLEL_EDGES_NOT_ALLOWED = "Nodes %s and %s are already connected by a different edge. To construct a graph that allows parallel edges, call allowsParallelEdges(true) on the Builder.";
    static const std::string SELF_LOOPS_NOT_ALLOWED = "Cannot add self-loop edge on node %s, as self-loops are not allowed. To construct a graph that allows self-loops, call allowsSelfLoops(true) on the Builder.";
    static const std::string NOT_AVAILABLE_ON_UNDIRECTED = "Cannot call source()/target() on a EndpointPair from an undirected graph. Consider calling adjacentNode(node) if you already have a node, or nodeU()/nodeV() if you don't.";
    static const std::string EDGE_ALREADY_EXISTS = "Edge %s already exists in the graph.";
    static const std::string GRAPH_STRING_FORMAT = "%s, nodes: %s, edges: %s";

    private GraphConstants() {
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
