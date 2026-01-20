#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableSortedSet/Builder.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ContiguousSet {
public:
   const DiscreteDomain<C> domain;

   public static <C : public Comparable> ContiguousSet<C> create(Range<C> range, DiscreteDomain<C> domain) {
      Preconditions.checkNotNull(range);
      Preconditions.checkNotNull(domain);
      Range<C> effectiveRange = range;

      try {
         if (!range.hasLowerBound()) {
            effectiveRange = effectiveRange.intersection(Range.atLeast(domain.minValue()));
         }

         if (!range.hasUpperBound()) {
            effectiveRange = effectiveRange.intersection(Range.atMost(domain.maxValue()));
         }
      } catch (NoSuchElementException var4) {
         throw IllegalArgumentException(var4);
      }

      boolean empty = effectiveRange.empty()
         || Range.compareOrThrow(range.lowerBound.leastValueAbove(domain), range.upperBound.greatestValueBelow(domain)) > 0;
      return (ContiguousSet<C>)(empty ? std::make_shared<EmptyContiguousSet>(domain) : std::make_shared<RegularContiguousSet>(effectiveRange, domain));
   }

   ContiguousSet(DiscreteDomain<C> domain) {
      super(Ordering.natural());
      this.domain = domain;
   }

   public ContiguousSet<C> headSet(C toElement) {
      return this.headSetImpl((C)Preconditions.checkNotNull(toElement), false);
   }

   public ContiguousSet<C> headSet(C toElement, boolean inclusive) {
      return this.headSetImpl((C)Preconditions.checkNotNull(toElement), inclusive);
   }

   public ContiguousSet<C> subSet(C fromElement, C toElement) {
      Preconditions.checkNotNull(fromElement);
      Preconditions.checkNotNull(toElement);
      Preconditions.checkArgument(this.comparator().compare(fromElement, toElement) <= 0);
      return this.subSetImpl(fromElement, true, toElement, false);
   }

   public ContiguousSet<C> subSet(C fromElement, boolean fromInclusive, C toElement, boolean toInclusive) {
      Preconditions.checkNotNull(fromElement);
      Preconditions.checkNotNull(toElement);
      Preconditions.checkArgument(this.comparator().compare(fromElement, toElement) <= 0);
      return this.subSetImpl(fromElement, fromInclusive, toElement, toInclusive);
   }

   public ContiguousSet<C> tailSet(C fromElement) {
      return this.tailSetImpl((C)Preconditions.checkNotNull(fromElement), true);
   }

   public ContiguousSet<C> tailSet(C fromElement, boolean inclusive) {
      return this.tailSetImpl((C)Preconditions.checkNotNull(fromElement), inclusive);
   }

   abstract ContiguousSet<C> headSetImpl(C var1, boolean var2);

   abstract ContiguousSet<C> subSetImpl(C var1, boolean var2, C var3, boolean var4);

   abstract ContiguousSet<C> tailSetImpl(C var1, boolean var2);

   public abstract ContiguousSet<C> intersection(ContiguousSet<C> var1);

   public abstract Range<C> range();

   public abstract Range<C> range(BoundType var1, BoundType var2);

    std::string toString() {
      return this.range();
   }

   public static <E> Builder<E> builder() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
