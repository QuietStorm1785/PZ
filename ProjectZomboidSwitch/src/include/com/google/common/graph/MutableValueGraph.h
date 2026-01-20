#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class MutableValueGraph {
public:
    virtual ~MutableValueGraph() = default;
    bool addNode(N var1);

    V putEdgeValue(N var1, N var2, V var3);

    bool removeNode(void* var1);

    V removeEdge(void* var1, void* var2);
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
