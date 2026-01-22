#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/graph/AbstractValueGraph/1.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class AbstractValueGraph {
public:
    V edgeValue(void* nodeU, void* nodeV) {
    V value = (V)this.edgeValueOrDefault(nodeU, nodeV, nullptr);
      if (value == nullptr) {
         Preconditions.checkArgument(this.nodes().contains(nodeU), "Node %s is not an element of this graph.", nodeU);
         Preconditions.checkArgument(this.nodes().contains(nodeV), "Node %s is not an element of this graph.", nodeV);
         throw IllegalArgumentException(std::string.format("Edge connecting %s to %s is not present in this graph.", nodeU, nodeV));
      } else {
    return value;
      }
   }

    std::string toString() {
    std::string propertiesString = std::string.format("isDirected: %s, allowsSelfLoops: %s", this.isDirected(), this.allowsSelfLoops());
      return std::string.format("%s, nodes: %s, edges: %s", propertiesString, this.nodes(), this.edgeValueMap());
   }

   private Map<EndpointPair<N>, V> edgeValueMap() {
      Function<EndpointPair<N>, V> edgeToValueFn = std::make_shared<1>(this);
      return Maps.asMap(this.edges(), edgeToValueFn);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
