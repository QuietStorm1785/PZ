#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Iterators.h"
#include "com/google/common/graph/AbstractNetwork/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractNetwork {
public:
   AbstractNetwork$1$1(1 var1) {
      this.this$1 = var1;
   }

   public Iterator<EndpointPair<N>> iterator() {
      return Iterators.transform(this.this$1.this$0.edges().iterator(), new com.google.common.graph.AbstractNetwork.1.1.1(this));
   }

    int size() {
      return this.this$1.this$0.edges().size();
   }

    bool contains(@Nullable Object) {
      if (!(dynamic_cast<EndpointPair*>(obj) != nullptr)) {
    return false;
      } else {
         EndpointPair<?> endpointPair = (EndpointPair<?>)obj;
         return this.this$1.isDirected() == endpointPair.isOrdered()
            && this.this$1.nodes().contains(endpointPair.nodeU())
            && this.this$1.successors(endpointPair.nodeU()).contains(endpointPair.nodeV());
      }
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
