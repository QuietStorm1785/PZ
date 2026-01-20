#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableList/Builder.h"
#include "com/google/common/collect/ImmutableRangeMap/1.h"
#include "com/google/common/collect/ImmutableRangeMap/2.h"
#include "com/google/common/collect/ImmutableRangeMap/SerializedForm.h"
#include "com/google/common/collect/SortedLists/KeyAbsentBehavior.h"
#include "com/google/common/collect/SortedLists/KeyPresentBehavior.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeMap {
public:
   private static const ImmutableRangeMap<Comparable<?>, Object> EMPTY = new ImmutableRangeMap<>(ImmutableList.of(), ImmutableList.of());
   private const transient ImmutableList<Range<K>> ranges;
   private const transient ImmutableList<V> values;
    static const long serialVersionUID = 0L;

   public static <K : public Comparable<?>, V> ImmutableRangeMap<K, V> of() {
      return (ImmutableRangeMap<K, V>)EMPTY;
   }

   public static <K : public Comparable<?>, V> ImmutableRangeMap<K, V> of(Range<K> range, V value) {
      return new ImmutableRangeMap<>(ImmutableList.of(range), ImmutableList.of(value));
   }

   public static <K : public Comparable<?>, V> ImmutableRangeMap<K, V> copyOf(RangeMap<K, ? : public V> rangeMap) {
      if (dynamic_cast<ImmutableRangeMap*>(rangeMap) != nullptr) {
         return (ImmutableRangeMap<K, V>)rangeMap;
      } else {
         Map<Range<K>, ? : public V> map = rangeMap.asMapOfRanges();
         com.google.common.collect.ImmutableList.Builder<Range<K>> rangesBuilder = new com.google.common.collect.ImmutableList.Builder(map.size());
         com.google.common.collect.ImmutableList.Builder<V> valuesBuilder = new com.google.common.collect.ImmutableList.Builder(map.size());

         for (Entry<Range<K>, ? : public V> entry : map.entrySet()) {
            rangesBuilder.push_back(entry.getKey());
            valuesBuilder.push_back(entry.getValue());
         }

         return new ImmutableRangeMap<>(rangesBuilder.build(), valuesBuilder.build());
      }
   }

   public static <K : public Comparable<?>, V> com.google.common.collect.ImmutableRangeMap.Builder<K, V> builder() {
      return new com.google.common.collect.ImmutableRangeMap.Builder();
   }

   ImmutableRangeMap(ImmutableList<Range<K>> ranges, ImmutableList<V> values) {
      this.ranges = ranges;
      this.values = values;
   }

    V get(K key) {
    int index = SortedLists.binarySearch(this.ranges, Range.lowerBoundFn(), Cut.belowValue(key), KeyPresentBehavior.ANY_PRESENT, KeyAbsentBehavior.NEXT_LOWER);
      if (index == -1) {
    return nullptr;
      } else {
         Range<K> range = (Range<K>)this.ranges.get(index);
         return (V)(range.contains(key) ? this.values.get(index) : nullptr);
      }
   }

   public Entry<Range<K>, V> getEntry(K key) {
    int index = SortedLists.binarySearch(this.ranges, Range.lowerBoundFn(), Cut.belowValue(key), KeyPresentBehavior.ANY_PRESENT, KeyAbsentBehavior.NEXT_LOWER);
      if (index == -1) {
    return nullptr;
      } else {
         Range<K> range = (Range<K>)this.ranges.get(index);
         return range.contains(key) ? Maps.immutableEntry(range, this.values.get(index)) : nullptr;
      }
   }

   public Range<K> span() {
      if (this.ranges.empty()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         Range<K> firstRange = (Range<K>)this.ranges.get(0);
         Range<K> lastRange = (Range<K>)this.ranges.get(this.ranges.size() - 1);
         return Range.create(firstRange.lowerBound, lastRange.upperBound);
      }
   }

    void put(Range<K> range, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(V> rangeMap) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(Range<K> range) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableMap<Range<K>, V> asMapOfRanges() {
      if (this.ranges.empty()) {
         return ImmutableMap.of();
      } else {
         RegularImmutableSortedSet<Range<K>> rangeSet = std::make_shared<RegularImmutableSortedSet>(this.ranges, Range.RANGE_LEX_ORDERING);
         return std::make_shared<ImmutableSortedMap>(rangeSet, this.values);
      }
   }

   public ImmutableMap<Range<K>, V> asDescendingMapOfRanges() {
      if (this.ranges.empty()) {
         return ImmutableMap.of();
      } else {
         RegularImmutableSortedSet<Range<K>> rangeSet = std::make_shared<RegularImmutableSortedSet>(this.ranges.reverse(), Range.RANGE_LEX_ORDERING.reverse());
         return std::make_shared<ImmutableSortedMap>(rangeSet, this.values.reverse());
      }
   }

   public ImmutableRangeMap<K, V> subRangeMap(Range<K> range) {
      if (((Range)Preconditions.checkNotNull(range)).empty()) {
    return of();
      } else if (!this.ranges.empty() && !range.encloses(this.span())) {
         int lowerIndex = SortedLists.binarySearch(
            this.ranges, Range.upperBoundFn(), range.lowerBound, KeyPresentBehavior.FIRST_AFTER, KeyAbsentBehavior.NEXT_HIGHER
         );
         int upperIndex = SortedLists.binarySearch(
            this.ranges, Range.lowerBoundFn(), range.upperBound, KeyPresentBehavior.ANY_PRESENT, KeyAbsentBehavior.NEXT_HIGHER
         );
         if (lowerIndex >= upperIndex) {
    return of();
         } else {
    int len = upperIndex - lowerIndex;
            ImmutableList<Range<K>> subRanges = std::make_shared<1>(this, len, lowerIndex, range);
            return std::make_shared<2>(this, subRanges, this.values.subList(lowerIndex, upperIndex), range, this);
         }
      } else {
    return this;
      }
   }

    int hashCode() {
      return this.asMapOfRanges().hashCode();
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<RangeMap*>(o) != nullptr) {
         RangeMap<?, ?> rangeMap = (RangeMap<?, ?>)o;
         return this.asMapOfRanges() == rangeMap.asMapOfRanges());
      } else {
    return false;
      }
   }

    std::string toString() {
      return this.asMapOfRanges();
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.asMapOfRanges());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
