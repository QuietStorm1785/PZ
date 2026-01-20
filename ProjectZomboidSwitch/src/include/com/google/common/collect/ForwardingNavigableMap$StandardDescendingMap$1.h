#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ForwardingNavigableMap/StandardDescendingMap.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingNavigableMap {
public:
   private Entry<K, V> toRemove;
   private Entry<K, V> nextOrNull;

   ForwardingNavigableMap$StandardDescendingMap$1(StandardDescendingMap var1) {
      this.this$1 = var1;
      this.toRemove = nullptr;
      this.nextOrNull = this.this$1.forward().lastEntry();
   }

    bool hasNext() {
      return this.nextOrNull != nullptr;
   }

   public Entry<K, V> next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    Entry var1;
         try {
            var1 = this.nextOrNull;
         } finally {
            this.toRemove = this.nextOrNull;
            this.nextOrNull = this.this$1.forward().lowerEntry(this.nextOrNull.getKey());
         }

    return var1;
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.toRemove != nullptr);
      this.this$1.forward().remove(this.toRemove.getKey());
      this.toRemove = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
