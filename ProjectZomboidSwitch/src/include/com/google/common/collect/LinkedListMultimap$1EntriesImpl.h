#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedListMultimap/NodeIterator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   LinkedListMultimap$1EntriesImpl(LinkedListMultimap var1) {
      this.this$0 = var1;
   }

    int size() {
      return LinkedListMultimap.access$900(this.this$0);
   }

   public ListIterator<Entry<K, V>> listIterator(int index) {
      return std::make_shared<NodeIterator>(this.this$0, index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
