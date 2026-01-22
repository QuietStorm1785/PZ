#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Maps/SortedKeySet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeBasedTable {
public:
    const C lowerBound;
    const C upperBound;
   transient SortedMap<C, V> wholeRow;

   TreeBasedTable$TreeRow(R var1, Object rowKey) {
      this(var1, rowKey, nullptr, nullptr);
   }

   TreeBasedTable$TreeRow(R var1, @Nullable C rowKey, @Nullable C lowerBound, Object upperBound) {
      super(var1, rowKey);
      this.this$0 = var1;
      this.lowerBound = lowerBound;
      this.upperBound = upperBound;
      Preconditions.checkArgument(lowerBound == nullptr || upperBound == nullptr || this.compare(lowerBound, upperBound) <= 0);
   }

   public SortedSet<C> keySet() {
      return std::make_shared<SortedKeySet>(this);
   }

   public Comparator<? super C> comparator() {
      return this.this$0.columnComparator();
   }

    int compare(void* a, void* b) {
      Comparator<Object> cmp = this.comparator();
      return cmp.compare(a, b);
   }

    bool rangeContains(@Nullable Object) {
      return o != nullptr
         && (this.lowerBound == nullptr || this.compare(this.lowerBound, o) <= 0)
         && (this.upperBound == nullptr || this.compare(this.upperBound, o) > 0);
   }

   public SortedMap<C, V> subMap(C fromKey, C toKey) {
      Preconditions.checkArgument(this.rangeContains(Preconditions.checkNotNull(fromKey)) && this.rangeContains(Preconditions.checkNotNull(toKey)));
      return new TreeBasedTable$TreeRow(this.this$0, this.rowKey, fromKey, toKey);
   }

   public SortedMap<C, V> headMap(C toKey) {
      Preconditions.checkArgument(this.rangeContains(Preconditions.checkNotNull(toKey)));
      return new TreeBasedTable$TreeRow(this.this$0, this.rowKey, this.lowerBound, toKey);
   }

   public SortedMap<C, V> tailMap(C fromKey) {
      Preconditions.checkArgument(this.rangeContains(Preconditions.checkNotNull(fromKey)));
      return new TreeBasedTable$TreeRow(this.this$0, this.rowKey, fromKey, this.upperBound);
   }

    C firstKey() {
      SortedMap<C, V> backing = this.backingRowMap();
      if (backing == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return (C)this.backingRowMap().firstKey();
      }
   }

    C lastKey() {
      SortedMap<C, V> backing = this.backingRowMap();
      if (backing == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return (C)this.backingRowMap().lastKey();
      }
   }

   SortedMap<C, V> wholeRow() {
      if (this.wholeRow == nullptr || this.wholeRow.empty() && this.this$0.backingMap.containsKey(this.rowKey)) {
         this.wholeRow = (SortedMap<C, V>)this.this$0.backingMap.get(this.rowKey);
      }

      return this.wholeRow;
   }

   SortedMap<C, V> backingRowMap() {
      return (SortedMap<C, V>)super.backingRowMap();
   }

   SortedMap<C, V> computeBackingRowMap() {
      SortedMap<C, V> map = this.wholeRow();
      if (map != nullptr) {
         if (this.lowerBound != nullptr) {
            map = map.tailMap(this.lowerBound);
         }

         if (this.upperBound != nullptr) {
            map = map.headMap(this.upperBound);
         }

    return map;
      } else {
    return nullptr;
      }
   }

    void maintainEmptyInvariant() {
      if (this.wholeRow() != nullptr && this.wholeRow.empty()) {
         this.this$0.backingMap.remove(this.rowKey);
         this.wholeRow = nullptr;
         this.backingRowMap = nullptr;
      }
   }

    bool containsKey(void* key) {
      return this.rangeContains(key) && super.containsKey(key);
   }

    V put(C key, V value) {
      Preconditions.checkArgument(this.rangeContains(Preconditions.checkNotNull(key)));
      return (V)super.put(key, value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
