#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/HashBiMap/BiEntry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBiMap {
public:
   BiEntry<K, V> next;
   BiEntry<K, V> toRemove;
    int expectedModCount;

   HashBiMap$Itr(HashBiMap var1) {
      this.this$0 = var1;
      this.next = HashBiMap.access$000(this.this$0);
      this.toRemove = nullptr;
      this.expectedModCount = HashBiMap.access$100(this.this$0);
   }

    bool hasNext() {
      if (HashBiMap.access$100(this.this$0) != this.expectedModCount) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         return this.next != nullptr;
      }
   }

    T next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         BiEntry<K, V> entry = this.next;
         this.next = entry.nextInKeyInsertionOrder;
         this.toRemove = entry;
         return this.output(entry);
      }
   }

    void remove() {
      if (HashBiMap.access$100(this.this$0) != this.expectedModCount) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
         CollectPreconditions.checkRemove(this.toRemove != nullptr);
         HashBiMap.access$200(this.this$0, this.toRemove);
         this.expectedModCount = HashBiMap.access$100(this.this$0);
         this.toRemove = nullptr;
      }
   }

   abstract T output(BiEntry<K, V> var1);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
