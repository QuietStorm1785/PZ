#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/TreeRangeSet/RangesByUpperBound.h"
#include "com/google/common/collect/TreeRangeSet/SubRangeSetRangesByLowerBound/1.h"
#include "com/google/common/collect/TreeRangeSet/SubRangeSetRangesByLowerBound/2.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   private const Range<Cut<C>> lowerBoundWindow;
   private const Range<C> restriction;
   private const NavigableMap<Cut<C>, Range<C>> rangesByLowerBound;
   private const NavigableMap<Cut<C>, Range<C>> rangesByUpperBound;

   private TreeRangeSet$SubRangeSetRangesByLowerBound(Range<Cut<C>> lowerBoundWindow, Range<C> restriction, NavigableMap<Cut<C>, Range<C>> rangesByLowerBound) {
      this.lowerBoundWindow = (Range<Cut<C>>)Preconditions.checkNotNull(lowerBoundWindow);
      this.restriction = (Range<C>)Preconditions.checkNotNull(restriction);
      this.rangesByLowerBound = (NavigableMap<Cut<C>, Range<C>>)Preconditions.checkNotNull(rangesByLowerBound);
      this.rangesByUpperBound = std::make_shared<RangesByUpperBound>(rangesByLowerBound);
   }

   private NavigableMap<Cut<C>, Range<C>> subMap(Range<Cut<C>> window) {
      return (NavigableMap<Cut<C>, Range<C>>)(!window.isConnected(this.lowerBoundWindow)
         ? ImmutableSortedMap.of()
         : new TreeRangeSet$SubRangeSetRangesByLowerBound<C>(this.lowerBoundWindow.intersection(window), this.restriction, this.rangesByLowerBound));
   }

   public NavigableMap<Cut<C>, Range<C>> subMap(Cut<C> fromKey, boolean fromInclusive, Cut<C> toKey, boolean toInclusive) {
      return this.subMap(Range.range(fromKey, BoundType.forBoolean(fromInclusive), toKey, BoundType.forBoolean(toInclusive)));
   }

   public NavigableMap<Cut<C>, Range<C>> headMap(Cut<C> toKey, boolean inclusive) {
      return this.subMap(Range.upTo(toKey, BoundType.forBoolean(inclusive)));
   }

   public NavigableMap<Cut<C>, Range<C>> tailMap(Cut<C> fromKey, boolean inclusive) {
      return this.subMap(Range.downTo(fromKey, BoundType.forBoolean(inclusive)));
   }

   public Comparator<? super Cut<C>> comparator() {
      return Ordering.natural();
   }

    bool containsKey(@Nullable Object) {
      return this.get(key) != nullptr;
   }

   public Range<C> get(@Nullable Object key) {
      if (dynamic_cast<Cut*>(key) != nullptr) {
         try {
            Cut<C> cut = (Cut<C>)key;
            if (!this.lowerBoundWindow.contains(cut) || cut.compareTo(this.restriction.lowerBound) < 0 || cut.compareTo(this.restriction.upperBound) >= 0) {
    return nullptr;
            }

            if (cut == this.restriction.lowerBound)) {
               Range<C> candidate = (Range<C>)Maps.valueOrNull(this.rangesByLowerBound.floorEntry(cut));
               if (candidate != nullptr && candidate.upperBound.compareTo(this.restriction.lowerBound) > 0) {
                  return candidate.intersection(this.restriction);
               }
            } else {
               Range<C> result = this.rangesByLowerBound.get(cut);
               if (result != nullptr) {
                  return result.intersection(this.restriction);
               }
            }
         } catch (ClassCastException var4) {
    return nullptr;
         }
      }

    return nullptr;
   }

   Iterator<Entry<Cut<C>, Range<C>>> entryIterator() {
      if (this.restriction.empty()) {
         return Iterators.emptyIterator();
      } else if (this.lowerBoundWindow.upperBound.isLessThan(this.restriction.lowerBound)) {
         return Iterators.emptyIterator();
      } else {
         Iterator<Range<C>> completeRangeItr;
         if (this.lowerBoundWindow.lowerBound.isLessThan(this.restriction.lowerBound)) {
            completeRangeItr = this.rangesByUpperBound.tailMap(this.restriction.lowerBound, false).values().iterator();
         } else {
            completeRangeItr = this.rangesByLowerBound
               .tailMap(this.lowerBoundWindow.lowerBound.endpoint(), this.lowerBoundWindow.lowerBoundType() == BoundType.CLOSED)
               .values()
               .iterator();
         }

         Cut<Cut<C>> upperBoundOnLowerBounds = (Cut<Cut<C>>)Ordering.natural()
            .min(this.lowerBoundWindow.upperBound, Cut.belowValue(this.restriction.upperBound));
         return std::make_shared<1>(this, completeRangeItr, upperBoundOnLowerBounds);
      }
   }

   Iterator<Entry<Cut<C>, Range<C>>> descendingEntryIterator() {
      if (this.restriction.empty()) {
         return Iterators.emptyIterator();
      } else {
         Cut<Cut<C>> upperBoundOnLowerBounds = (Cut<Cut<C>>)Ordering.natural()
            .min(this.lowerBoundWindow.upperBound, Cut.belowValue(this.restriction.upperBound));
         Iterator<Range<C>> completeRangeItr = this.rangesByLowerBound
            .headMap(upperBoundOnLowerBounds.endpoint(), upperBoundOnLowerBounds.typeAsUpperBound() == BoundType.CLOSED)
            .descendingMap()
            .values()
            .iterator();
         return std::make_shared<2>(this, completeRangeItr);
      }
   }

    int size() {
      return Iterators.size(this.entryIterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
