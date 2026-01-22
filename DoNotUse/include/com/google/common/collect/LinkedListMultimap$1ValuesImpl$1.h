#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedListMultimap/1ValuesImpl.h"
#include "com/google/common/collect/LinkedListMultimap/NodeIterator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   LinkedListMultimap$1ValuesImpl$1(1ValuesImpl var1, ListIterator x0, NodeIterator var3) {
      super(x0);
      this.this$1 = var1;
      this.val$nodeItr = var3;
   }

    V transform(V> entry) {
      return (V)entry.getValue();
   }

    void set(V value) {
      this.val$nodeItr.setValue(value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
