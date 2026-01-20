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


class Network {
public:
    virtual ~Network() = default;
   Set<N> nodes();

   Set<E> edges();

   Graph<N> asGraph();

    bool isDirected();

    bool allowsParallelEdges();

    bool allowsSelfLoops();

   ElementOrder<N> nodeOrder();

   ElementOrder<E> edgeOrder();

   Set<N> adjacentNodes(Object var1);

   Set<N> predecessors(Object var1);

   Set<N> successors(Object var1);

   Set<E> incidentEdges(Object var1);

   Set<E> inEdges(Object var1);

   Set<E> outEdges(Object var1);

    int degree(void* var1);

    int inDegree(void* var1);

    int outDegree(void* var1);

   EndpointPair<N> incidentNodes(Object var1);

   Set<E> adjacentEdges(Object var1);

   Set<E> edgesConnecting(Object var1, Object var2);

    bool equals(@Nullable Object);

    int hashCode();
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
