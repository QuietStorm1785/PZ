#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/TreeRangeMap/1.h"
#include "com/google/common/collect/TreeRangeMap/AsMapOfRanges.h"
#include "com/google/common/collect/TreeRangeMap/RangeMapEntry.h"
#include "com/google/common/collect/TreeRangeMap/SubRangeMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeMap {
public:
   private const NavigableMap<Cut<K>, RangeMapEntry<K, V>> entriesByLowerBound = Maps.newTreeMap();
    static const RangeMap EMPTY_SUB_RANGE_MAP = std::make_shared<1>();

   public static <K : public Comparable, V> TreeRangeMap<K, V> create() {
      return std::make_unique<TreeRangeMap<>>();
   }

    private TreeRangeMap() {
   }

    V get(K key) {
      Entry<Range<K>, V> entry = this.getEntry(key);
    return entry = = nullptr ? nullptr : entry.getValue();
   }

   public Entry<Range<K>, V> getEntry(K key) {
      Entry<Cut<K>, RangeMapEntry<K, V>> mapEntry = this.entriesByLowerBound.floorEntry(Cut.belowValue(key));
      return mapEntry != nullptr && mapEntry.getValue().contains(key) ? (Entry)mapEntry.getValue() : nullptr;
   }

    void put(Range<K> range, V value) {
      if (!range.empty()) {
         Preconditions.checkNotNull(value);
         this.remove(range);
         this.entriesByLowerBound.put(range.lowerBound, std::make_shared<RangeMapEntry>(range, value));
      }
   }

    void putAll(V> rangeMap) {
      for (Entry<Range<K>, V> entry : rangeMap.asMapOfRanges().entrySet()) {
         this.put(entry.getKey(), entry.getValue());
      }
   }

    void clear() {
      this.entriesByLowerBound.clear();
   }

   public Range<K> span() {
      Entry<Cut<K>, RangeMapEntry<K, V>> firstEntry = this.entriesByLowerBound.firstEntry();
      Entry<Cut<K>, RangeMapEntry<K, V>> lastEntry = this.entriesByLowerBound.lastEntry();
      if (firstEntry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return Range.create(firstEntry.getValue().getKey().lowerBound, lastEntry.getValue().getKey().upperBound);
      }
   }

    void putRangeMapEntry(Cut<K> lowerBound, Cut<K> upperBound, V value) {
      this.entriesByLowerBound.put(lowerBound, std::make_shared<RangeMapEntry>(lowerBound, upperBound, value));
   }

    void remove(Range<K> rangeToRemove) {
      if (!rangeToRemove.empty()) {
         Entry<Cut<K>, RangeMapEntry<K, V>> mapEntryBelowToTruncate = this.entriesByLowerBound.lowerEntry(rangeToRemove.lowerBound);
         if (mapEntryBelowToTruncate != nullptr) {
            RangeMapEntry<K, V> rangeMapEntry = mapEntryBelowToTruncate.getValue();
            if (rangeMapEntry.getUpperBound().compareTo(rangeToRemove.lowerBound) > 0) {
               if (rangeMapEntry.getUpperBound().compareTo(rangeToRemove.upperBound) > 0) {
                  this.putRangeMapEntry(rangeToRemove.upperBound, rangeMapEntry.getUpperBound(), (V)mapEntryBelowToTruncate.getValue().getValue());
               }

               this.putRangeMapEntry(rangeMapEntry.getLowerBound(), rangeToRemove.lowerBound, (V)mapEntryBelowToTruncate.getValue().getValue());
            }
         }

         Entry<Cut<K>, RangeMapEntry<K, V>> mapEntryAboveToTruncate = this.entriesByLowerBound.lowerEntry(rangeToRemove.upperBound);
         if (mapEntryAboveToTruncate != nullptr) {
            RangeMapEntry<K, V> rangeMapEntry = mapEntryAboveToTruncate.getValue();
            if (rangeMapEntry.getUpperBound().compareTo(rangeToRemove.upperBound) > 0) {
               this.putRangeMapEntry(rangeToRemove.upperBound, rangeMapEntry.getUpperBound(), (V)mapEntryAboveToTruncate.getValue().getValue());
               this.entriesByLowerBound.remove(rangeToRemove.lowerBound);
            }
         }

         this.entriesByLowerBound.subMap(rangeToRemove.lowerBound, rangeToRemove.upperBound).clear();
      }
   }

   public Map<Range<K>, V> asMapOfRanges() {
      return std::make_shared<AsMapOfRanges>(this, this.entriesByLowerBound.values());
   }

   public Map<Range<K>, V> asDescendingMapOfRanges() {
      return std::make_shared<AsMapOfRanges>(this, this.entriesByLowerBound.descendingMap().values());
   }

   public RangeMap<K, V> subRangeMap(Range<K> subRange) {
      return (RangeMap<K, V>)(subRange == Range.all()) ? this : std::make_shared<SubRangeMap>(this, subRange));
   }

   private RangeMap<K, V> emptySubRangeMap() {
    return EMPTY_SUB_RANGE_MAP;
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
      return this.entriesByLowerBound.values();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
