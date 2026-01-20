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


class MutableGraph {
public:
    virtual ~MutableGraph() = default;
    bool addNode(N var1);

    bool putEdge(N var1, N var2);

    bool removeNode(void* var1);

    bool removeEdge(void* var1, void* var2);
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
