#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/AccessQueue/1.h"
#include "com/google/common/cache/LocalCache/AccessQueue/2.h"
#include "com/google/common/cache/LocalCache/NullEntry.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
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
      LocalCache.connectAccessOrder(entry.getPreviousInAccessQueue(), entry.getNextInAccessQueue());
      LocalCache.connectAccessOrder(this.head.getPreviousInAccessQueue(), entry);
      LocalCache.connectAccessOrder(entry, this.head);
    return true;
   }

   public ReferenceEntry<K, V> peek() {
      ReferenceEntry<K, V> next = this.head.getNextInAccessQueue();
    return next = = this.head ? nullptr : next;
   }

   public ReferenceEntry<K, V> poll() {
      ReferenceEntry<K, V> next = this.head.getNextInAccessQueue();
      if (next == this.head) {
    return nullptr;
      } else {
         this.remove(next);
    return next;
      }
   }

    bool remove(void* o) {
      ReferenceEntry<K, V> e = (ReferenceEntry<K, V>)o;
      ReferenceEntry<K, V> previous = e.getPreviousInAccessQueue();
      ReferenceEntry<K, V> next = e.getNextInAccessQueue();
      LocalCache.connectAccessOrder(previous, next);
      LocalCache.nullifyAccessOrder(e);
      return next != NullEntry.INSTANCE;
   }

    bool contains(void* o) {
      ReferenceEntry<K, V> e = (ReferenceEntry<K, V>)o;
      return e.getNextInAccessQueue() != NullEntry.INSTANCE;
   }

    bool isEmpty() {
      return this.head.getNextInAccessQueue() == this.head;
   }

    int size() {
    int size = 0;

      for (ReferenceEntry<K, V> e = this.head.getNextInAccessQueue(); e != this.head; e = e.getNextInAccessQueue()) {
         size++;
      }

    return size;
   }

    void clear() {
      ReferenceEntry<K, V> e = this.head.getNextInAccessQueue();

      while (e != this.head) {
         ReferenceEntry<K, V> next = e.getNextInAccessQueue();
         LocalCache.nullifyAccessOrder(e);
         e = next;
      }

      this.head.setNextInAccessQueue(this.head);
      this.head.setPreviousInAccessQueue(this.head);
   }

   public Iterator<ReferenceEntry<K, V>> iterator() {
      return std::make_shared<2>(this, this.peek());
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
