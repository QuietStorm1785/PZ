#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/Iterators.h"
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace graph {


class EdgesConnecting {
public:
   private const Map<?, E> nodeToOutEdge;
    const void* targetNode;

   EdgesConnecting(Map<?, E> nodeToEdgeMap, Object targetNode) {
      this.nodeToOutEdge = (Map<?, E>)Preconditions.checkNotNull(nodeToEdgeMap);
      this.targetNode = Preconditions.checkNotNull(targetNode);
   }

   public UnmodifiableIterator<E> iterator() {
    E connectingEdge = this.getConnectingEdge();
    return connectingEdge = = nullptr ? ImmutableSet.of().iterator() : Iterators.singletonIterator(connectingEdge);
   }

    int size() {
      return this.getConnectingEdge() == nullptr ? 0 : 1;
   }

    bool contains(@Nullable Object) {
    E connectingEdge = this.getConnectingEdge();
      return connectingEdge != nullptr && connectingEdge == edge);
   }

    E getConnectingEdge() {
      return this.nodeToOutEdge.get(this.targetNode);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
