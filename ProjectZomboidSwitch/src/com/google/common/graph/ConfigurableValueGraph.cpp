#include "com\google\common\graph/ConfigurableValueGraph.h"

namespace com {
namespace google {
namespace common {
namespace graph {

bool ConfigurableValueGraph::isDirected() {
    // TODO: Implement isDirected
    return false;
}

bool ConfigurableValueGraph::allowsSelfLoops() {
    // TODO: Implement allowsSelfLoops
    return false;
}

V ConfigurableValueGraph::edgeValueOrDefault(void* nodeU, void* nodeV, @Nullable V) {
    // TODO: Implement edgeValueOrDefault
    return nullptr;
}

long ConfigurableValueGraph::edgeCount() {
    // TODO: Implement edgeCount
    return 0;
}

bool ConfigurableValueGraph::containsNode(@Nullable Object) {
    // TODO: Implement containsNode
    return false;
}

} // namespace graph
} // namespace common
} // namespace google
} // namespace com
