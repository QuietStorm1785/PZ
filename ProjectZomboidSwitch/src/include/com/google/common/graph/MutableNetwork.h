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


class MutableNetwork {
public:
    virtual ~MutableNetwork() = default;
    bool addNode(N var1);

    bool addEdge(N var1, N var2, E var3);

    bool removeNode(void* var1);

    bool removeEdge(void* var1);
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
