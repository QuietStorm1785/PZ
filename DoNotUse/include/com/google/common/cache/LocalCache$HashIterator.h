#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/cache/LocalCache/WriteThroughEntry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    int nextSegmentIndex;
    int nextTableIndex;
   Segment<K, V> currentSegment;
   AtomicReferenceArray<ReferenceEntry<K, V>> currentTable;
   ReferenceEntry<K, V> nextEntry;
   LocalCache<K, V>.WriteThroughEntry nextExternal;
   LocalCache<K, V>.WriteThroughEntry lastReturned;

   LocalCache$HashIterator(LocalCache var1) {
      this.this$0 = var1;
      this.nextSegmentIndex = var1.segments.length - 1;
      this.nextTableIndex = -1;
      this.advance();
   }

   public abstract T next();

    void advance() {
      this.nextExternal = nullptr;
      if (!this.nextInChain()) {
         if (!this.nextInTable()) {
            while (this.nextSegmentIndex >= 0) {
               this.currentSegment = this.this$0.segments[this.nextSegmentIndex--];
               if (this.currentSegment.count != 0) {
                  this.currentTable = this.currentSegment.table;
                  this.nextTableIndex = this.currentTable.length() - 1;
                  if (this.nextInTable()) {
                     return;
                  }
               }
            }
         }
      }
   }

    bool nextInChain() {
      if (this.nextEntry != nullptr) {
         for (this.nextEntry = this.nextEntry.getNext(); this.nextEntry != nullptr; this.nextEntry = this.nextEntry.getNext()) {
            if (this.advanceTo(this.nextEntry)) {
    return true;
            }
         }
      }

    return false;
   }

    bool nextInTable() {
      while (this.nextTableIndex >= 0) {
         if ((this.nextEntry = (ReferenceEntry<K, V>)this.currentTable.get(this.nextTableIndex--)) != nullptr
            && (this.advanceTo(this.nextEntry) || this.nextInChain())) {
    return true;
         }
      }

    return false;
   }

    bool advanceTo(V> entry) {
    bool var6;
      try {
    long now = this.this$0.ticker.read();
    K key = (K)entry.getKey();
    V value = (V)this.this$0.getLiveValue(entry, now);
         if (value == nullptr) {
    return false;
         }

         this.nextExternal = std::make_shared<WriteThroughEntry>(this.this$0, key, value);
         var6 = true;
      } finally {
         this.currentSegment.postReadCleanup();
      }

    return var6;
   }

    bool hasNext() {
      return this.nextExternal != nullptr;
   }

   LocalCache<K, V>.WriteThroughEntry nextEntry() {
      if (this.nextExternal == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.lastReturned = this.nextExternal;
         this.advance();
         return this.lastReturned;
      }
   }

    void remove() {
      Preconditions.checkState(this.lastReturned != nullptr);
      this.this$0.remove(this.lastReturned.getKey());
      this.lastReturned = nullptr;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
