#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/LinkedListMultimap/KeyList.h"
#include "com/google/common/collect/LinkedListMultimap/Node.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
    const void* key;
    int nextIndex;
   Node<K, V> next;
   Node<K, V> current;
   Node<K, V> previous;

   LinkedListMultimap$ValueForKeyIterator(@Nullable LinkedListMultimap var1, Object key) {
      this.this$0 = var1;
      this.key = key;
      KeyList<K, V> keyList = (KeyList<K, V>)LinkedListMultimap.access$600(var1).get(key);
      this.next = keyList == nullptr ? nullptr : keyList.head;
   }

   public LinkedListMultimap$ValueForKeyIterator(@Nullable LinkedListMultimap var1, Object key, int index) {
      this.this$0 = var1;
      KeyList<K, V> keyList = (KeyList<K, V>)LinkedListMultimap.access$600(var1).get(key);
    int size = keyList == nullptr ? 0 : keyList.count;
      Preconditions.checkPositionIndex(index, size);
      if (index >= size / 2) {
         this.previous = keyList == nullptr ? nullptr : keyList.tail;
         this.nextIndex = size;

         while (index++ < size) {
            this.previous();
         }
      } else {
         this.next = keyList == nullptr ? nullptr : keyList.head;

         while (index-- > 0) {
            this.next();
         }
      }

      this.key = key;
      this.current = nullptr;
   }

    bool hasNext() {
      return this.next != nullptr;
   }

    V next() {
      LinkedListMultimap.access$300(this.next);
      this.previous = this.current = this.next;
      this.next = this.next.nextSibling;
      this.nextIndex++;
      return (V)this.current.value;
   }

    bool hasPrevious() {
      return this.previous != nullptr;
   }

    V previous() {
      LinkedListMultimap.access$300(this.previous);
      this.next = this.current = this.previous;
      this.previous = this.previous.previousSibling;
      this.nextIndex--;
      return (V)this.current.value;
   }

    int nextIndex() {
      return this.nextIndex;
   }

    int previousIndex() {
      return this.nextIndex - 1;
   }

    void remove() {
      CollectPreconditions.checkRemove(this.current != nullptr);
      if (this.current != this.next) {
         this.previous = this.current.previousSibling;
         this.nextIndex--;
      } else {
         this.next = this.current.nextSibling;
      }

      LinkedListMultimap.access$400(this.this$0, this.current);
      this.current = nullptr;
   }

    void set(V value) {
      Preconditions.checkState(this.current != nullptr);
      this.current.value = value;
   }

    void add(V value) {
      this.previous = LinkedListMultimap.access$700(this.this$0, this.key, value, this.next);
      this.nextIndex++;
      this.current = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
