#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/MapMakerInternalMap/InternalEntry.h"
#include "com/google/common/collect/MapMakerInternalMap/Segment.h"
#include "com/google/common/collect/MapMakerInternalMap/WriteThroughEntry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class MapMakerInternalMap {
public:
    int nextSegmentIndex;
    int nextTableIndex;
   Segment<K, V, E, S> currentSegment;
   AtomicReferenceArray<E> currentTable;
    E nextEntry;
   MapMakerInternalMap<K, V, E, S>.WriteThroughEntry nextExternal;
   MapMakerInternalMap<K, V, E, S>.WriteThroughEntry lastReturned;

   MapMakerInternalMap$HashIterator(MapMakerInternalMap var1) {
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
         for (this.nextEntry = (E)this.nextEntry.getNext(); this.nextEntry != nullptr; this.nextEntry = (E)this.nextEntry.getNext()) {
            if (this.advanceTo(this.nextEntry)) {
    return true;
            }
         }
      }

    return false;
   }

    bool nextInTable() {
      while (this.nextTableIndex >= 0) {
         if ((this.nextEntry = (E)((InternalEntry)this.currentTable.get(this.nextTableIndex--))) != nullptr
            && (this.advanceTo(this.nextEntry) || this.nextInChain())) {
    return true;
         }
      }

    return false;
   }

    bool advanceTo(E entry) {
    bool var4;
      try {
    K key = (K)entry.getKey();
    V value = (V)this.this$0.getLiveValue(entry);
         if (value == nullptr) {
    return false;
         }

         this.nextExternal = std::make_shared<WriteThroughEntry>(this.this$0, key, value);
         var4 = true;
      } finally {
         this.currentSegment.postReadCleanup();
      }

    return var4;
   }

    bool hasNext() {
      return this.nextExternal != nullptr;
   }

   MapMakerInternalMap<K, V, E, S>.WriteThroughEntry nextEntry() {
      if (this.nextExternal == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.lastReturned = this.nextExternal;
         this.advance();
         return this.lastReturned;
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.lastReturned != nullptr);
      this.this$0.remove(this.lastReturned.getKey());
      this.lastReturned = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
