#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Iterables.h"
#include "com/google/common/collect/Iterators.h"
#include "com/google/common/collect/Sets.h"
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "com/google/common/math/IntMath.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractDirectedNetworkConnections {
public:
   AbstractDirectedNetworkConnections$1(AbstractDirectedNetworkConnections var1) {
      this.this$0 = var1;
   }

   public UnmodifiableIterator<E> iterator() {
      Iterable<E> incidentEdges = (Iterable<E>)(AbstractDirectedNetworkConnections.access$000(this.this$0) == 0
         ? Iterables.concat(this.this$0.inEdgeMap.keySet(), this.this$0.outEdgeMap.keySet())
         : Sets.union(this.this$0.inEdgeMap.keySet(), this.this$0.outEdgeMap.keySet()));
      return Iterators.unmodifiableIterator(incidentEdges.iterator());
   }

    int size() {
      return IntMath.saturatedAdd(this.this$0.inEdgeMap.size(), this.this$0.outEdgeMap.size() - AbstractDirectedNetworkConnections.access$000(this.this$0));
   }

    bool contains(@Nullable Object) {
      return this.this$0.inEdgeMap.containsKey(obj) || this.this$0.outEdgeMap.containsKey(obj);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
