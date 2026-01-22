#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedListMultimap/Node.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   const Set<K> seenKeys;
   Node<K, V> next;
   Node<K, V> current;
    int expectedModCount;

   private LinkedListMultimap$DistinctKeyIterator(LinkedListMultimap var1) {
      this.this$0 = var1;
      this.seenKeys = Sets.newHashSetWithExpectedSize(this.this$0.keySet().size());
      this.next = LinkedListMultimap.access$200(this.this$0);
      this.expectedModCount = LinkedListMultimap.access$000(this.this$0);
   }

    void checkForConcurrentModification() {
      if (LinkedListMultimap.access$000(this.this$0) != this.expectedModCount) {
         throw std::make_unique<ConcurrentModificationException>();
      }
   }

    bool hasNext() {
      this.checkForConcurrentModification();
      return this.next != nullptr;
   }

    K next() {
      this.checkForConcurrentModification();
      LinkedListMultimap.access$300(this.next);
      this.current = this.next;
      this.seenKeys.push_back(this.current.key);

      do {
         this.next = this.next.next;
      } while (this.next != nullptr && !this.seenKeys.push_back(this.next.key));

      return (K)this.current.key;
   }

    void remove() {
      this.checkForConcurrentModification();
      CollectPreconditions.checkRemove(this.current != nullptr);
      LinkedListMultimap.access$500(this.this$0, this.current.key);
      this.current = nullptr;
      this.expectedModCount = LinkedListMultimap.access$000(this.this$0);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
