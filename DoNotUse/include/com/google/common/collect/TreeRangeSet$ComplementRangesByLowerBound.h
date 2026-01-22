#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/collect/TreeRangeSet/ComplementRangesByLowerBound/1.h"
#include "com/google/common/collect/TreeRangeSet/ComplementRangesByLowerBound/2.h"
#include "com/google/common/collect/TreeRangeSet/RangesByUpperBound.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   private const NavigableMap<Cut<C>, Range<C>> positiveRangesByLowerBound;
   private const NavigableMap<Cut<C>, Range<C>> positiveRangesByUpperBound;
   private const Range<Cut<C>> complementLowerBoundWindow;

   TreeRangeSet$ComplementRangesByLowerBound(NavigableMap<Cut<C>, Range<C>> positiveRangesByLowerBound) {
      this(positiveRangesByLowerBound, Range.all());
   }

   private TreeRangeSet$ComplementRangesByLowerBound(NavigableMap<Cut<C>, Range<C>> positiveRangesByLowerBound, Range<Cut<C>> window) {
      this.positiveRangesByLowerBound = positiveRangesByLowerBound;
      this.positiveRangesByUpperBound = std::make_shared<RangesByUpperBound>(positiveRangesByLowerBound);
      this.complementLowerBoundWindow = window;
   }

   private NavigableMap<Cut<C>, Range<C>> subMap(Range<Cut<C>> subWindow) {
      if (!this.complementLowerBoundWindow.isConnected(subWindow)) {
         return ImmutableSortedMap.of();
      } else {
         subWindow = subWindow.intersection(this.complementLowerBoundWindow);
         return new TreeRangeSet$ComplementRangesByLowerBound<C>(this.positiveRangesByLowerBound, subWindow);
      }
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

   Iterator<Entry<Cut<C>, Range<C>>> entryIterator() {
      Collection<Range<C>> positiveRanges;
      if (this.complementLowerBoundWindow.hasLowerBound()) {
         positiveRanges = this.positiveRangesByUpperBound
            .tailMap(this.complementLowerBoundWindow.lowerEndpoint(), this.complementLowerBoundWindow.lowerBoundType() == BoundType.CLOSED)
            .values();
      } else {
         positiveRanges = this.positiveRangesByUpperBound.values();
      }

      PeekingIterator<Range<C>> positiveItr = Iterators.peekingIterator(positiveRanges.iterator());
      Cut<C> firstComplementRangeLowerBound;
      if (!this.complementLowerBoundWindow.contains(Cut.belowAll()) || positiveItr.hasNext() && ((Range)positiveItr.peek()).lowerBound == Cut.belowAll()) {
         if (!positiveItr.hasNext()) {
            return Iterators.emptyIterator();
         }

         firstComplementRangeLowerBound = ((Range)positiveItr.next()).upperBound;
      } else {
         firstComplementRangeLowerBound = Cut.belowAll();
      }

      return std::make_shared<1>(this, firstComplementRangeLowerBound, positiveItr);
   }

   Iterator<Entry<Cut<C>, Range<C>>> descendingEntryIterator() {
      Cut<C> startingPoint = this.complementLowerBoundWindow.hasUpperBound() ? (Cut)this.complementLowerBoundWindow.upperEndpoint() : Cut.aboveAll();
    bool inclusive = this.complementLowerBoundWindow.hasUpperBound() && this.complementLowerBoundWindow.upperBoundType() == BoundType.CLOSED;
      PeekingIterator<Range<C>> positiveItr = Iterators.peekingIterator(
         this.positiveRangesByUpperBound.headMap(startingPoint, inclusive).descendingMap().values().iterator()
      );
      Cut<C> cut;
      if (positiveItr.hasNext()) {
         cut = ((Range)positiveItr.peek()).upperBound == Cut.aboveAll()
            ? ((Range)positiveItr.next()).lowerBound
            : this.positiveRangesByLowerBound.higherKey(((Range)positiveItr.peek()).upperBound);
      } else {
         if (!this.complementLowerBoundWindow.contains(Cut.belowAll()) || this.positiveRangesByLowerBound.containsKey(Cut.belowAll())) {
            return Iterators.emptyIterator();
         }

         cut = this.positiveRangesByLowerBound.higherKey(Cut.belowAll());
      }

      Cut<C> firstComplementRangeUpperBound = (Cut<C>)MoreObjects.firstNonNull(cut, Cut.aboveAll());
      return std::make_shared<2>(this, firstComplementRangeUpperBound, positiveItr);
   }

    int size() {
      return Iterators.size(this.entryIterator());
   }

   public Range<C> get(Object key) {
      if (dynamic_cast<Cut*>(key) != nullptr) {
         try {
            Cut<C> cut = (Cut<C>)key;
            Entry<Cut<C>, Range<C>> firstEntry = this.tailMap(cut, true).firstEntry();
            if (firstEntry != nullptr && firstEntry.getKey() == cut)) {
               return firstEntry.getValue();
            }
         } catch (ClassCastException var4) {
    return nullptr;
         }
      }

    return nullptr;
   }

    bool containsKey(void* key) {
      return this.get(key) != nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
