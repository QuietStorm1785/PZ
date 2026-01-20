#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedListMultimap/DistinctKeyIterator.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   LinkedListMultimap$1KeySetImpl(LinkedListMultimap var1) {
      this.this$0 = var1;
   }

    int size() {
      return LinkedListMultimap.access$600(this.this$0).size();
   }

   public Iterator<K> iterator() {
      return std::make_shared<DistinctKeyIterator>(this.this$0, nullptr);
   }

    bool contains(void* key) {
      return this.this$0.containsKey(key);
   }

    bool remove(void* o) {
      return !this.this$0.removeAll(o).empty();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
