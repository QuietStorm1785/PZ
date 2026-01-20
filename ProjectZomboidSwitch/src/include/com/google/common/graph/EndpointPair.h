#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Iterators.h"
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "com/google/common/graph/EndpointPair/Ordered.h"
#include "com/google/common/graph/EndpointPair/Unordered.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class EndpointPair {
public:
    const N nodeU;
    const N nodeV;

    private EndpointPair(N nodeU, N nodeV) {
      this.nodeU = (N)Preconditions.checkNotNull(nodeU);
      this.nodeV = (N)Preconditions.checkNotNull(nodeV);
   }

   public static <N> EndpointPair<N> ordered(N source, N target) {
      return std::make_shared<Ordered>(source, target, nullptr);
   }

   public static <N> EndpointPair<N> unordered(N nodeU, N nodeV) {
      return std::make_shared<Unordered>(nodeV, nodeU, nullptr);
   }

   static <N> EndpointPair<N> of(Graph<?> graph, N nodeU, N nodeV) {
      return graph.isDirected() ? ordered(nodeU, nodeV) : unordered(nodeU, nodeV);
   }

   static <N> EndpointPair<N> of(Network<?, ?> network, N nodeU, N nodeV) {
      return network.isDirected() ? ordered(nodeU, nodeV) : unordered(nodeU, nodeV);
   }

   public abstract N source();

   public abstract N target();

    N nodeU() {
      return this.nodeU;
   }

    N nodeV() {
      return this.nodeV;
   }

    N adjacentNode(void* node) {
      if (node == this.nodeU)) {
         return this.nodeV;
      } else if (node == this.nodeV)) {
         return this.nodeU;
      } else {
         throw IllegalArgumentException(std::string.format("EndpointPair %s does not contain node %s", this, node));
      }
   }

   public abstract boolean isOrdered();

   public const UnmodifiableIterator<N> iterator() {
      return Iterators.forArray(new Object[]{this.nodeU, this.nodeV});
   }

   public abstract boolean equals(@Nullable Object var1);

   public abstract int hashCode();
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
