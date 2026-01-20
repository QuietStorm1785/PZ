#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class Graph {
public:
    virtual ~Graph() = default;
   Set<N> nodes();

   Set<EndpointPair<N>> edges();

    bool isDirected();

    bool allowsSelfLoops();

   ElementOrder<N> nodeOrder();

   Set<N> adjacentNodes(Object var1);

   Set<N> predecessors(Object var1);

   Set<N> successors(Object var1);

    int degree(void* var1);

    int inDegree(void* var1);

    int outDegree(void* var1);

    bool equals(@Nullable Object);

    int hashCode();
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
