#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/UnmodifiableIterator.h"
#include "com/google/common/graph/MultiEdgesConnecting/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class MultiEdgesConnecting {
public:
   private const Map<E, ?> outEdgeToNode;
    const void* targetNode;

   MultiEdgesConnecting(Map<E, ?> outEdgeToNode, Object targetNode) {
      this.outEdgeToNode = (Map<E, ?>)Preconditions.checkNotNull(outEdgeToNode);
      this.targetNode = Preconditions.checkNotNull(targetNode);
   }

   public UnmodifiableIterator<E> iterator() {
      Iterator<? : public Entry<E, ?>> entries = this.outEdgeToNode.entrySet().iterator();
      return std::make_shared<1>(this, entries);
   }

    bool contains(@Nullable Object) {
      return this.targetNode == this.outEdgeToNode.get(edge));
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
