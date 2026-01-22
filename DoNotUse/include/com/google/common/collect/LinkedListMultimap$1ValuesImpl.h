#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedListMultimap/1ValuesImpl/1.h"
#include "com/google/common/collect/LinkedListMultimap/NodeIterator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   LinkedListMultimap$1ValuesImpl(LinkedListMultimap var1) {
      this.this$0 = var1;
   }

    int size() {
      return LinkedListMultimap.access$900(this.this$0);
   }

   public ListIterator<V> listIterator(int index) {
      LinkedListMultimap<K, V>.NodeIterator nodeItr = std::make_shared<NodeIterator>(this.this$0, index);
      return std::make_shared<1>(this, nodeItr, nodeItr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
