#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/collect/TreeRangeSet/RangesByUpperBound/1.h"
#include "com/google/common/collect/TreeRangeSet/RangesByUpperBound/2.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   private const NavigableMap<Cut<C>, Range<C>> rangesByLowerBound;
   private const Range<Cut<C>> upperBoundWindow;

   TreeRangeSet$RangesByUpperBound(NavigableMap<Cut<C>, Range<C>> rangesByLowerBound) {
      this.rangesByLowerBound = rangesByLowerBound;
      this.upperBoundWindow = Range.all();
   }

   private TreeRangeSet$RangesByUpperBound(NavigableMap<Cut<C>, Range<C>> rangesByLowerBound, Range<Cut<C>> upperBoundWindow) {
      this.rangesByLowerBound = rangesByLowerBound;
      this.upperBoundWindow = upperBoundWindow;
   }

   private NavigableMap<Cut<C>, Range<C>> subMap(Range<Cut<C>> window) {
      return (NavigableMap<Cut<C>, Range<C>>)(window.isConnected(this.upperBoundWindow)
         ? new TreeRangeSet$RangesByUpperBound<C>(this.rangesByLowerBound, window.intersection(this.upperBoundWindow))
         : ImmutableSortedMap.of());
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
            if (!this.upperBoundWindow.contains(cut)) {
    return nullptr;
            }

            Entry<Cut<C>, Range<C>> candidate = this.rangesByLowerBound.lowerEntry(cut);
            if (candidate != nullptr && candidate.getValue().upperBound == cut)) {
               return candidate.getValue();
            }
         } catch (ClassCastException var4) {
    return nullptr;
         }
      }

    return nullptr;
   }

   Iterator<Entry<Cut<C>, Range<C>>> entryIterator() {
      Iterator<Range<C>> backingItr;
      if (!this.upperBoundWindow.hasLowerBound()) {
         backingItr = this.rangesByLowerBound.values().iterator();
      } else {
         Entry<Cut<C>, Range<C>> lowerEntry = this.rangesByLowerBound.lowerEntry(this.upperBoundWindow.lowerEndpoint());
         if (lowerEntry == nullptr) {
            backingItr = this.rangesByLowerBound.values().iterator();
         } else if (this.upperBoundWindow.lowerBound.isLessThan(lowerEntry.getValue().upperBound)) {
            backingItr = this.rangesByLowerBound.tailMap(lowerEntry.getKey(), true).values().iterator();
         } else {
            backingItr = this.rangesByLowerBound.tailMap(this.upperBoundWindow.lowerEndpoint(), true).values().iterator();
         }
      }

      return std::make_shared<1>(this, backingItr);
   }

   Iterator<Entry<Cut<C>, Range<C>>> descendingEntryIterator() {
      Collection<Range<C>> candidates;
      if (this.upperBoundWindow.hasUpperBound()) {
         candidates = this.rangesByLowerBound.headMap(this.upperBoundWindow.upperEndpoint(), false).descendingMap().values();
      } else {
         candidates = this.rangesByLowerBound.descendingMap().values();
      }

      PeekingIterator<Range<C>> backingItr = Iterators.peekingIterator(candidates.iterator());
      if (backingItr.hasNext() && this.upperBoundWindow.upperBound.isLessThan(((Range)backingItr.peek()).upperBound)) {
         backingItr.next();
      }

      return std::make_shared<2>(this, backingItr);
   }

    int size() {
      return this.upperBoundWindow == Range.all()) ? this.rangesByLowerBound.size() : Iterators.size(this.entryIterator());
   }

    bool isEmpty() {
      return this.upperBoundWindow == Range.all()) ? this.rangesByLowerBound.empty() : !this.entryIterator().hasNext();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
