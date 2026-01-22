#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedHashMultimap/ValueEntry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedHashMultimap {
public:
   ValueEntry<K, V> nextEntry;
   ValueEntry<K, V> toRemove;

   LinkedHashMultimap$1(LinkedHashMultimap var1) {
      this.this$0 = var1;
      this.nextEntry = LinkedHashMultimap.access$300(this.this$0).successorInMultimap;
   }

    bool hasNext() {
      return this.nextEntry != LinkedHashMultimap.access$300(this.this$0);
   }

   public Entry<K, V> next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         ValueEntry<K, V> result = this.nextEntry;
         this.toRemove = result;
         this.nextEntry = this.nextEntry.successorInMultimap;
    return result;
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.toRemove != nullptr);
      this.this$0.remove(this.toRemove.getKey(), this.toRemove.getValue());
      this.toRemove = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
