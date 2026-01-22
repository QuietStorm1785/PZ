#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "com/google/common/primitives/Ints.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractGraph {
public:
   AbstractGraph$1(AbstractGraph var1) {
      this.this$0 = var1;
   }

   public UnmodifiableIterator<EndpointPair<N>> iterator() {
      return EndpointPairIterator.of(this.this$0);
   }

    int size() {
      return Ints.saturatedCast(this.this$0.edgeCount());
   }

    bool contains(@Nullable Object) {
      if (!(dynamic_cast<EndpointPair*>(obj) != nullptr)) {
    return false;
      } else {
         EndpointPair<?> endpointPair = (EndpointPair<?>)obj;
         return this.this$0.isDirected() == endpointPair.isOrdered()
            && this.this$0.nodes().contains(endpointPair.nodeU())
            && this.this$0.successors(endpointPair.nodeU()).contains(endpointPair.nodeV());
      }
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
