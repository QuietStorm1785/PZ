#include "com\google\common\graph/AbstractDirectedNetworkConnections.h"

namespace com {
namespace google {
namespace common {
namespace graph {

protected AbstractDirectedNetworkConnections::AbstractDirectedNetworkConnections(N> inEdgeMap, N> outEdgeMap, int selfLoopCount) {
    // TODO: Implement AbstractDirectedNetworkConnections
    return nullptr;
}

N AbstractDirectedNetworkConnections::oppositeNode(void* edge) {
    // TODO: Implement oppositeNode
    return nullptr;
}

N AbstractDirectedNetworkConnections::removeInEdge(void* edge, bool isSelfLoop) {
    // TODO: Implement removeInEdge
    return nullptr;
}

N AbstractDirectedNetworkConnections::removeOutEdge(void* edge) {
    // TODO: Implement removeOutEdge
    return nullptr;
}

void AbstractDirectedNetworkConnections::addInEdge(E edge, N node, bool isSelfLoop) {
    // TODO: Implement addInEdge
}

void AbstractDirectedNetworkConnections::addOutEdge(E edge, N node) {
    // TODO: Implement addOutEdge
}

} // namespace graph
} // namespace common
} // namespace google
} // namespace com
