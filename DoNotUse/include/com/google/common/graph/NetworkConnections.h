#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class NetworkConnections {
public:
    virtual ~NetworkConnections() = default;
   Set<N> adjacentNodes();

   Set<N> predecessors();

   Set<N> successors();

   Set<E> incidentEdges();

   Set<E> inEdges();

   Set<E> outEdges();

   Set<E> edgesConnecting(Object var1);

    N oppositeNode(void* var1);

    N removeInEdge(void* var1, bool var2);

    N removeOutEdge(void* var1);

    void addInEdge(E var1, N var2, bool var3);

    void addOutEdge(E var1, N var2);
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
