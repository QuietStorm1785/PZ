#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class GraphConnections {
public:
    virtual ~GraphConnections() = default;
   Set<N> adjacentNodes();

   Set<N> predecessors();

   Set<N> successors();

    V value(void* var1);

    void removePredecessor(void* var1);

    V removeSuccessor(void* var1);

    void addPredecessor(N var1, V var2);

    V addSuccessor(N var1, V var2);
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
