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
#include "com/google/common/collect/ImmutableRangeSet/1.h"
#include "com/google/common/collect/ImmutableRangeSet/AsSet.h"
#include "com/google/common/collect/ImmutableRangeSet/Builder.h"
#include "com/google/common/collect/ImmutableRangeSet/ComplementRanges.h"
#include "com/google/common/collect/ImmutableRangeSet/SerializedForm.h"
#include "com/google/common/collect/SortedLists/KeyAbsentBehavior.h"
#include "com/google/common/collect/SortedLists/KeyPresentBehavior.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeSet {
public:
   private static const ImmutableRangeSet<Comparable<?>> EMPTY = new ImmutableRangeSet<>(ImmutableList.of());
   private static const ImmutableRangeSet<Comparable<?>> ALL = new ImmutableRangeSet<>(ImmutableList.of(Range.all()));
   private const transient ImmutableList<Range<C>> ranges;
   private transient ImmutableRangeSet<C> complement;

   public static <C : public Comparable> ImmutableRangeSet<C> of() {
    return EMPTY;
   }

   static <C : public Comparable> ImmutableRangeSet<C> all() {
    return ALL;
   }

   public static <C : public Comparable> ImmutableRangeSet<C> of(Range<C> range) {
      Preconditions.checkNotNull(range);
      if (range.empty()) {
    return of();
      } else {
         return range == Range.all()) ? all() : new ImmutableRangeSet<>(ImmutableList.of(range));
      }
   }

   public static <C : public Comparable> ImmutableRangeSet<C> copyOf(RangeSet<C> rangeSet) {
      Preconditions.checkNotNull(rangeSet);
      if (rangeSet.empty()) {
    return of();
      } else if (rangeSet.encloses(Range.all())) {
    return all();
      } else {
         if (dynamic_cast<ImmutableRangeSet*>(rangeSet) != nullptr) {
            ImmutableRangeSet<C> immutableRangeSet = (ImmutableRangeSet<C>)rangeSet;
            if (!immutableRangeSet.isPartialView()) {
    return immutableRangeSet;
            }
         }

         return new ImmutableRangeSet<>(ImmutableList.copyOf(rangeSet.asRanges()));
      }
   }

   ImmutableRangeSet(ImmutableList<Range<C>> ranges) {
      this.ranges = ranges;
   }

    private ImmutableRangeSet(ImmutableList<Range<C>> ranges, ImmutableRangeSet<C> complement) {
      this.ranges = ranges;
      this.complement = complement;
   }

    bool intersects(Range<C> otherRange) {
      int ceilingIndex = SortedLists.binarySearch(
         this.ranges, Range.lowerBoundFn(), otherRange.lowerBound, Ordering.natural(), KeyPresentBehavior.ANY_PRESENT, KeyAbsentBehavior.NEXT_HIGHER
      );
      return ceilingIndex < this.ranges.size()
            && ((Range)this.ranges.get(ceilingIndex)).isConnected(otherRange)
            && !((Range)this.ranges.get(ceilingIndex)).intersection(otherRange).empty()
         ? true
         : ceilingIndex > 0
            && ((Range)this.ranges.get(ceilingIndex - 1)).isConnected(otherRange)
            && !((Range)this.ranges.get(ceilingIndex - 1)).intersection(otherRange).empty();
   }

    bool encloses(Range<C> otherRange) {
      int index = SortedLists.binarySearch(
         this.ranges, Range.lowerBoundFn(), otherRange.lowerBound, Ordering.natural(), KeyPresentBehavior.ANY_PRESENT, KeyAbsentBehavior.NEXT_LOWER
      );
      return index != -1 && ((Range)this.ranges.get(index)).encloses(otherRange);
   }

   public Range<C> rangeContaining(C value) {
      int index = SortedLists.binarySearch(
         this.ranges, Range.lowerBoundFn(), Cut.belowValue(value), Ordering.natural(), KeyPresentBehavior.ANY_PRESENT, KeyAbsentBehavior.NEXT_LOWER
      );
      if (index != -1) {
         Range<C> range = (Range<C>)this.ranges.get(index);
         return range.contains(value) ? range : nullptr;
      } else {
    return nullptr;
      }
   }

   public Range<C> span() {
      if (this.ranges.empty()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return Range.create(((Range)this.ranges.get(0)).lowerBound, ((Range)this.ranges.get(this.ranges.size() - 1)).upperBound);
      }
   }

    bool isEmpty() {
      return this.ranges.empty();
   }

    void add(Range<C> range) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void addAll(RangeSet<C> other) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(Range<C> range) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void removeAll(RangeSet<C> other) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ImmutableSet<Range<C>> asRanges() {
      return (ImmutableSet<Range<C>>)(this.ranges.empty() ? ImmutableSet.of() : std::make_shared<RegularImmutableSortedSet>(this.ranges, Range.RANGE_LEX_ORDERING));
   }

   public ImmutableSet<Range<C>> asDescendingSetOfRanges() {
      return (ImmutableSet<Range<C>>)(this.ranges.empty()
         ? ImmutableSet.of()
         : std::make_shared<RegularImmutableSortedSet>(this.ranges.reverse(), Range.RANGE_LEX_ORDERING.reverse()));
   }

   public ImmutableRangeSet<C> complement() {
      ImmutableRangeSet<C> result = this.complement;
      if (result != nullptr) {
    return result;
      } else if (this.ranges.empty()) {
         return this.complement = all();
      } else if (this.ranges.size() == 1 && ((Range)this.ranges.get(0)) == Range.all())) {
         return this.complement = of();
      } else {
         ImmutableList<Range<C>> complementRanges = std::make_shared<ComplementRanges>(this);
         return this.complement = new ImmutableRangeSet<>(complementRanges, this);
      }
   }

   private ImmutableList<Range<C>> intersectRanges(Range<C> range) {
      if (this.ranges.empty() || range.empty()) {
         return ImmutableList.of();
      } else if (range.encloses(this.span())) {
         return this.ranges;
      } else {
    int fromIndex;
         if (range.hasLowerBound()) {
            fromIndex = SortedLists.binarySearch(
               this.ranges, Range.upperBoundFn(), range.lowerBound, KeyPresentBehavior.FIRST_AFTER, KeyAbsentBehavior.NEXT_HIGHER
            );
         } else {
            fromIndex = 0;
         }

    int toIndex;
         if (range.hasUpperBound()) {
            toIndex = SortedLists.binarySearch(
               this.ranges, Range.lowerBoundFn(), range.upperBound, KeyPresentBehavior.FIRST_PRESENT, KeyAbsentBehavior.NEXT_HIGHER
            );
         } else {
            toIndex = this.ranges.size();
         }

    int length = toIndex - fromIndex;
         return (ImmutableList<Range<C>>)(length == 0 ? ImmutableList.of() : std::make_shared<1>(this, length, fromIndex, range));
      }
   }

   public ImmutableRangeSet<C> subRangeSet(Range<C> range) {
      if (!this.empty()) {
         Range<C> span = this.span();
         if (range.encloses(span)) {
    return this;
         }

         if (range.isConnected(span)) {
            return new ImmutableRangeSet<>(this.intersectRanges(range));
         }
      }

    return of();
   }

   public ImmutableSortedSet<C> asSet(DiscreteDomain<C> domain) {
      Preconditions.checkNotNull(domain);
      if (this.empty()) {
         return ImmutableSortedSet.of();
      } else {
         Range<C> span = this.span().canonical(domain);
         if (!span.hasLowerBound()) {
            throw IllegalArgumentException("Neither the DiscreteDomain nor this range set are bounded below");
         } else {
            if (!span.hasUpperBound()) {
               try {
                  domain.maxValue();
               } catch (NoSuchElementException var4) {
                  throw IllegalArgumentException("Neither the DiscreteDomain nor this range set are bounded above");
               }
            }

            return std::make_shared<AsSet>(this, domain);
         }
      }
   }

    bool isPartialView() {
      return this.ranges.isPartialView();
   }

   public static <C : public Comparable<?>> Builder<C> builder() {
      return std::make_unique<Builder>();
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.ranges);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
