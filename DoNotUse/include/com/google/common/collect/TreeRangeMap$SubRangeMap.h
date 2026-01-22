#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/TreeRangeMap/RangeMapEntry.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/1.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap/SubRangeMapAsMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   private const Range<K> subRange;

   TreeRangeMap$SubRangeMap(Range<K> var1, Range subRange) {
      this.this$0 = var1;
      this.subRange = subRange;
   }

    V get(K key) {
      return (V)(this.subRange.contains(key) ? this.this$0.get(key) : nullptr);
   }

   public Entry<Range<K>, V> getEntry(K key) {
      if (this.subRange.contains(key)) {
         Entry<Range<K>, V> entry = this.this$0.getEntry(key);
         if (entry != nullptr) {
            return Maps.immutableEntry(((Range)entry.getKey()).intersection(this.subRange), entry.getValue());
         }
      }

    return nullptr;
   }

   public Range<K> span() {
      Entry<Cut<K>, RangeMapEntry<K, V>> lowerEntry = TreeRangeMap.access$000(this.this$0).floorEntry(this.subRange.lowerBound);
      Cut<K> lowerBound;
      if (lowerEntry != nullptr && ((RangeMapEntry)lowerEntry.getValue()).getUpperBound().compareTo(this.subRange.lowerBound) > 0) {
         lowerBound = this.subRange.lowerBound;
      } else {
         lowerBound = TreeRangeMap.access$000(this.this$0).ceilingKey(this.subRange.lowerBound);
         if (lowerBound == nullptr || lowerBound.compareTo(this.subRange.upperBound) >= 0) {
            throw std::make_unique<NoSuchElementException>();
         }
      }

      Entry<Cut<K>, RangeMapEntry<K, V>> upperEntry = TreeRangeMap.access$000(this.this$0).lowerEntry(this.subRange.upperBound);
      if (upperEntry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         Cut<K> upperBound;
         if (((RangeMapEntry)upperEntry.getValue()).getUpperBound().compareTo(this.subRange.upperBound) >= 0) {
            upperBound = this.subRange.upperBound;
         } else {
            upperBound = ((RangeMapEntry)upperEntry.getValue()).getUpperBound();
         }

         return Range.create(lowerBound, upperBound);
      }
   }

    void put(Range<K> range, V value) {
      Preconditions.checkArgument(this.subRange.encloses(range), "Cannot put range %s into a subRangeMap(%s)", range, this.subRange);
      this.this$0.put(range, value);
   }

    void putAll(V> rangeMap) {
      if (!rangeMap.asMapOfRanges().empty()) {
         Range<K> span = rangeMap.span();
         Preconditions.checkArgument(this.subRange.encloses(span), "Cannot putAll rangeMap with span %s into a subRangeMap(%s)", span, this.subRange);
         this.this$0.putAll(rangeMap);
      }
   }

    void clear() {
      this.this$0.remove(this.subRange);
   }

    void remove(Range<K> range) {
      if (range.isConnected(this.subRange)) {
         this.this$0.remove(range.intersection(this.subRange));
      }
   }

   public RangeMap<K, V> subRangeMap(Range<K> range) {
      return !range.isConnected(this.subRange) ? TreeRangeMap.access$100(this.this$0) : this.this$0.subRangeMap(range.intersection(this.subRange));
   }

   public Map<Range<K>, V> asMapOfRanges() {
      return std::make_shared<SubRangeMapAsMap>(this);
   }

   public Map<Range<K>, V> asDescendingMapOfRanges() {
      return std::make_shared<1>(this);
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<RangeMap*>(o) != nullptr) {
         RangeMap<?, ?> rangeMap = (RangeMap<?, ?>)o;
         return this.asMapOfRanges() == rangeMap.asMapOfRanges());
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.asMapOfRanges().hashCode();
   }

    std::string toString() {
      return this.asMapOfRanges();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
