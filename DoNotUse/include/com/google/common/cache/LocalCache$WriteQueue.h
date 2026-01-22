#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/NullEntry.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/WriteQueue/1.h"
#include "com/google/common/cache/LocalCache/WriteQueue/2.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   const ReferenceEntry<K, V> head = std::make_shared<1>(this);

    bool offer(V> entry) {
      LocalCache.connectWriteOrder(entry.getPreviousInWriteQueue(), entry.getNextInWriteQueue());
      LocalCache.connectWriteOrder(this.head.getPreviousInWriteQueue(), entry);
      LocalCache.connectWriteOrder(entry, this.head);
    return true;
   }

   public ReferenceEntry<K, V> peek() {
      ReferenceEntry<K, V> next = this.head.getNextInWriteQueue();
    return next = = this.head ? nullptr : next;
   }

   public ReferenceEntry<K, V> poll() {
      ReferenceEntry<K, V> next = this.head.getNextInWriteQueue();
      if (next == this.head) {
    return nullptr;
      } else {
         this.remove(next);
    return next;
      }
   }

    bool remove(void* o) {
      ReferenceEntry<K, V> e = (ReferenceEntry<K, V>)o;
      ReferenceEntry<K, V> previous = e.getPreviousInWriteQueue();
      ReferenceEntry<K, V> next = e.getNextInWriteQueue();
      LocalCache.connectWriteOrder(previous, next);
      LocalCache.nullifyWriteOrder(e);
      return next != NullEntry.INSTANCE;
   }

    bool contains(void* o) {
      ReferenceEntry<K, V> e = (ReferenceEntry<K, V>)o;
      return e.getNextInWriteQueue() != NullEntry.INSTANCE;
   }

    bool isEmpty() {
      return this.head.getNextInWriteQueue() == this.head;
   }

    int size() {
    int size = 0;

      for (ReferenceEntry<K, V> e = this.head.getNextInWriteQueue(); e != this.head; e = e.getNextInWriteQueue()) {
         size++;
      }

    return size;
   }

    void clear() {
      ReferenceEntry<K, V> e = this.head.getNextInWriteQueue();

      while (e != this.head) {
         ReferenceEntry<K, V> next = e.getNextInWriteQueue();
         LocalCache.nullifyWriteOrder(e);
         e = next;
      }

      this.head.setNextInWriteQueue(this.head);
      this.head.setPreviousInWriteQueue(this.head);
   }

   public Iterator<ReferenceEntry<K, V>> iterator() {
      return std::make_shared<2>(this, this.peek());
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
