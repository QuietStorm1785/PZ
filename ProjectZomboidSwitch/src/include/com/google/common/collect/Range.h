#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Range/1.h"
#include "com/google/common/collect/Range/2.h"
#include "com/google/common/collect/Range/3.h"
#include "com/google/common/collect/Range/RangeLexOrdering.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Range {
public:
   private static const Function<Range, Cut> LOWER_BOUND_FN = std::make_unique<1>();
   private static const Function<Range, Cut> UPPER_BOUND_FN = std::make_unique<2>();
   static const Ordering<Range<?>> RANGE_LEX_ORDERING = std::make_shared<RangeLexOrdering>(nullptr);
   private static const Range<Comparable> ALL = new Range<>(Cut.belowAll(), Cut.aboveAll());
   const Cut<C> lowerBound;
   const Cut<C> upperBound;
    static const long serialVersionUID = 0L;

   static <C : public Comparable<?>> Function<Range<C>, Cut<C>> lowerBoundFn() {
    return LOWER_BOUND_FN;
   }

   static <C : public Comparable<?>> Function<Range<C>, Cut<C>> upperBoundFn() {
    return UPPER_BOUND_FN;
   }

   static <C : public Comparable<?>> Range<C> create(Cut<C> lowerBound, Cut<C> upperBound) {
      return new Range<>(lowerBound, upperBound);
   }

   public static <C : public Comparable<?>> Range<C> open(C lower, C upper) {
    return create();
   }

   public static <C : public Comparable<?>> Range<C> closed(C lower, C upper) {
    return create();
   }

   public static <C : public Comparable<?>> Range<C> closedOpen(C lower, C upper) {
    return create();
   }

   public static <C : public Comparable<?>> Range<C> openClosed(C lower, C upper) {
    return create();
   }

   public static <C : public Comparable<?>> Range<C> range(C lower, BoundType lowerType, C upper, BoundType upperType) {
      Preconditions.checkNotNull(lowerType);
      Preconditions.checkNotNull(upperType);
      Cut<C> lowerBound = lowerType == BoundType.OPEN ? Cut.aboveValue(lower) : Cut.belowValue(lower);
      Cut<C> upperBound = upperType == BoundType.OPEN ? Cut.belowValue(upper) : Cut.aboveValue(upper);
    return create();
   }

   public static <C : public Comparable<?>> Range<C> lessThan(C endpoint) {
    return create();
   }

   public static <C : public Comparable<?>> Range<C> atMost(C endpoint) {
    return create();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public static <C : public Comparable<?>> Range<C> upTo(C endpoint, BoundType boundType) {
      switch (3.$SwitchMap$com$google$common$collect$BoundType[boundType.ordinal()]) {
         case 1:
    return lessThan();
         case 2:
    return atMost();
         default:
            throw std::make_unique<AssertionError>();
      }
   }

   public static <C : public Comparable<?>> Range<C> greaterThan(C endpoint) {
    return create();
   }

   public static <C : public Comparable<?>> Range<C> atLeast(C endpoint) {
    return create();
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public static <C : public Comparable<?>> Range<C> downTo(C endpoint, BoundType boundType) {
      switch (3.$SwitchMap$com$google$common$collect$BoundType[boundType.ordinal()]) {
         case 1:
    return greaterThan();
         case 2:
    return atLeast();
         default:
            throw std::make_unique<AssertionError>();
      }
   }

   public static <C : public Comparable<?>> Range<C> all() {
      return (Range<C>)ALL;
   }

   public static <C : public Comparable<?>> Range<C> singleton(C value) {
    return closed();
   }

   public static <C : public Comparable<?>> Range<C> encloseAll(Iterable<C> values) {
      Preconditions.checkNotNull(values);
      if (dynamic_cast<ContiguousSet*>(values) != nullptr) {
         return ((ContiguousSet)values).range();
      } else {
         Iterator<C> valueIterator = values.iterator();
    C min = (C)Preconditions.checkNotNull(valueIterator.next());
    C max = min;

         while (valueIterator.hasNext()) {
    C value = (C)Preconditions.checkNotNull(valueIterator.next());
            min = (C)Ordering.natural().min(min, value);
            max = (C)Ordering.natural().max(max, value);
         }

    return closed();
      }
   }

    private Range(Cut<C> lowerBound, Cut<C> upperBound) {
      this.lowerBound = (Cut<C>)Preconditions.checkNotNull(lowerBound);
      this.upperBound = (Cut<C>)Preconditions.checkNotNull(upperBound);
      if (lowerBound.compareTo(upperBound) > 0 || lowerBound == Cut.aboveAll() || upperBound == Cut.belowAll()) {
         throw IllegalArgumentException("Invalid range: " + toString(lowerBound, upperBound));
      }
   }

    bool hasLowerBound() {
      return this.lowerBound != Cut.belowAll();
   }

    C lowerEndpoint() {
      return (C)this.lowerBound.endpoint();
   }

    BoundType lowerBoundType() {
      return this.lowerBound.typeAsLowerBound();
   }

    bool hasUpperBound() {
      return this.upperBound != Cut.aboveAll();
   }

    C upperEndpoint() {
      return (C)this.upperBound.endpoint();
   }

    BoundType upperBoundType() {
      return this.upperBound.typeAsUpperBound();
   }

    bool isEmpty() {
      return this.lowerBound == this.upperBound);
   }

    bool contains(C value) {
      Preconditions.checkNotNull(value);
      return this.lowerBound.isLessThan(value) && !this.upperBound.isLessThan(value);
   }

    bool apply(C input) {
      return this.contains(input);
   }

    bool containsAll(Iterable<? extends) {
      if (Iterables.isEmpty(values)) {
    return true;
      } else {
         if (dynamic_cast<SortedSet*>(values) != nullptr) {
            SortedSet<? : public C> set = cast(values);
            Comparator<?> comparator = set.comparator();
            if (Ordering.natural() == comparator) || comparator == nullptr) {
               return this.contains((C)set.first()) && this.contains((C)set.last());
            }
         }

    for (auto& value : values)            if (!this.contains(value)) {
    return false;
            }
         }

    return true;
      }
   }

    bool encloses(Range<C> other) {
      return this.lowerBound.compareTo(other.lowerBound) <= 0 && this.upperBound.compareTo(other.upperBound) >= 0;
   }

    bool isConnected(Range<C> other) {
      return this.lowerBound.compareTo(other.upperBound) <= 0 && other.lowerBound.compareTo(this.upperBound) <= 0;
   }

   public Range<C> intersection(Range<C> connectedRange) {
    int lowerCmp = this.lowerBound.compareTo(connectedRange.lowerBound);
    int upperCmp = this.upperBound.compareTo(connectedRange.upperBound);
      if (lowerCmp >= 0 && upperCmp <= 0) {
    return this;
      } else if (lowerCmp <= 0 && upperCmp >= 0) {
    return connectedRange;
      } else {
         Cut<C> newLower = lowerCmp >= 0 ? this.lowerBound : connectedRange.lowerBound;
         Cut<C> newUpper = upperCmp <= 0 ? this.upperBound : connectedRange.upperBound;
    return create();
      }
   }

   public Range<C> span(Range<C> other) {
    int lowerCmp = this.lowerBound.compareTo(other.lowerBound);
    int upperCmp = this.upperBound.compareTo(other.upperBound);
      if (lowerCmp <= 0 && upperCmp >= 0) {
    return this;
      } else if (lowerCmp >= 0 && upperCmp <= 0) {
    return other;
      } else {
         Cut<C> newLower = lowerCmp <= 0 ? this.lowerBound : other.lowerBound;
         Cut<C> newUpper = upperCmp >= 0 ? this.upperBound : other.upperBound;
    return create();
      }
   }

   public Range<C> canonical(DiscreteDomain<C> domain) {
      Preconditions.checkNotNull(domain);
      Cut<C> lower = this.lowerBound.canonical(domain);
      Cut<C> upper = this.upperBound.canonical(domain);
    return lower = = this.lowerBound && upper == this.upperBound ? this : create(lower, upper);
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<Range*>(object) != nullptr)) {
    return false;
      } else {
         Range<?> other = (Range<?>)object;
         return this.lowerBound == other.lowerBound) && this.upperBound == other.upperBound);
      }
   }

    int hashCode() {
      return this.lowerBound.hashCode() * 31 + this.upperBound.hashCode();
   }

    std::string toString() {
    return toString();
   }

    static std::string toString(Cut<?> lowerBound, Cut<?> upperBound) {
    std::stringstream sb = new std::stringstream(16);
      lowerBound.describeAsLowerBound(sb);
      sb.append("..");
      upperBound.describeAsUpperBound(sb);
      return sb;
   }

   private static <T> SortedSet<T> cast(Iterable<T> iterable) {
      return (SortedSet<T>)iterable;
   }

    void* readResolve() {
      return this == ALL) ? all() : this;
   }

    static int compareOrThrow(Comparable left, Comparable right) {
      return left.compareTo(right);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
