#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/LinkedListMultimap/Node.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
    int nextIndex;
   Node<K, V> next;
   Node<K, V> current;
   Node<K, V> previous;
    int expectedModCount;

   LinkedListMultimap$NodeIterator(LinkedListMultimap var1, int index) {
      this.this$0 = var1;
      this.expectedModCount = LinkedListMultimap.access$000(this.this$0);
    int size = var1.size();
      Preconditions.checkPositionIndex(index, size);
      if (index >= size / 2) {
         this.previous = LinkedListMultimap.access$100(var1);
         this.nextIndex = size;

         while (index++ < size) {
            this.previous();
         }
      } else {
         this.next = LinkedListMultimap.access$200(var1);

         while (index-- > 0) {
            this.next();
         }
      }

      this.current = nullptr;
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

   public Node<K, V> next() {
      this.checkForConcurrentModification();
      LinkedListMultimap.access$300(this.next);
      this.previous = this.current = this.next;
      this.next = this.next.next;
      this.nextIndex++;
      return this.current;
   }

    void remove() {
      this.checkForConcurrentModification();
      CollectPreconditions.checkRemove(this.current != nullptr);
      if (this.current != this.next) {
         this.previous = this.current.previous;
         this.nextIndex--;
      } else {
         this.next = this.current.next;
      }

      LinkedListMultimap.access$400(this.this$0, this.current);
      this.current = nullptr;
      this.expectedModCount = LinkedListMultimap.access$000(this.this$0);
   }

    bool hasPrevious() {
      this.checkForConcurrentModification();
      return this.previous != nullptr;
   }

   public Node<K, V> previous() {
      this.checkForConcurrentModification();
      LinkedListMultimap.access$300(this.previous);
      this.next = this.current = this.previous;
      this.previous = this.previous.previous;
      this.nextIndex--;
      return this.current;
   }

    int nextIndex() {
      return this.nextIndex;
   }

    int previousIndex() {
      return this.nextIndex - 1;
   }

    void set(V> e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void add(V> e) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setValue(V value) {
      Preconditions.checkState(this.current != nullptr);
      this.current.value = value;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
