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
#include "com/google/common/collect/RegularContiguousSet/1.h"
#include "com/google/common/collect/RegularContiguousSet/2.h"
#include "com/google/common/collect/RegularContiguousSet/SerializedForm.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularContiguousSet {
public:
   private const Range<C> range;
    static const long serialVersionUID = 0L;

   RegularContiguousSet(Range<C> range, DiscreteDomain<C> domain) {
      super(domain);
      this.range = range;
   }

   private ContiguousSet<C> intersectionInCurrentDomain(Range<C> other) {
      return (ContiguousSet<C>)(this.range.isConnected(other)
         ? ContiguousSet.create(this.range.intersection(other), this.domain)
         : std::make_shared<EmptyContiguousSet>(this.domain));
   }

   ContiguousSet<C> headSetImpl(C toElement, boolean inclusive) {
      return this.intersectionInCurrentDomain(Range.upTo(toElement, BoundType.forBoolean(inclusive)));
   }

   ContiguousSet<C> subSetImpl(C fromElement, boolean fromInclusive, C toElement, boolean toInclusive) {
      return (ContiguousSet<C>)(fromElement.compareTo(toElement) == 0 && !fromInclusive && !toInclusive
         ? std::make_shared<EmptyContiguousSet>(this.domain)
         : this.intersectionInCurrentDomain(Range.range(fromElement, BoundType.forBoolean(fromInclusive), toElement, BoundType.forBoolean(toInclusive))));
   }

   ContiguousSet<C> tailSetImpl(C fromElement, boolean inclusive) {
      return this.intersectionInCurrentDomain(Range.downTo(fromElement, BoundType.forBoolean(inclusive)));
   }

    int indexOf(void* target) {
      return this.contains(target) ? (int)this.domain.distance(this.first(), (Comparable)target) : -1;
   }

   public UnmodifiableIterator<C> iterator() {
      return std::make_shared<1>(this, this.first());
   }

   public UnmodifiableIterator<C> descendingIterator() {
      return std::make_shared<2>(this, this.last());
   }

    static bool equalsOrThrow(Comparable<?> left, @Nullable Comparable<?>) {
      return right != nullptr && Range.compareOrThrow(left, right) == 0;
   }

    bool isPartialView() {
    return false;
   }

    C first() {
      return (C)this.range.lowerBound.leastValueAbove(this.domain);
   }

    C last() {
      return (C)this.range.upperBound.greatestValueBelow(this.domain);
   }

    int size() {
    long distance = this.domain.distance(this.first(), this.last());
      return distance >= 2147483647L ? int.MAX_VALUE : (int)distance + 1;
   }

    bool contains(@Nullable Object) {
      if (object == nullptr) {
    return false;
      } else {
         try {
            return this.range.contains((Comparable)object);
         } catch (ClassCastException var3) {
    return false;
         }
      }
   }

    bool containsAll(Collection<?> targets) {
      return Collections2.containsAllImpl(this, targets);
   }

    bool isEmpty() {
    return false;
   }

   public ContiguousSet<C> intersection(ContiguousSet<C> other) {
      Preconditions.checkNotNull(other);
      Preconditions.checkArgument(this.domain == other.domain));
      if (other.empty()) {
    return other;
      } else {
    C lowerEndpoint = (C)Ordering.natural().max(this.first(), other.first());
    C upperEndpoint = (C)Ordering.natural().min(this.last(), other.last());
         return (ContiguousSet<C>)(lowerEndpoint.compareTo(upperEndpoint) <= 0
            ? ContiguousSet.create(Range.closed(lowerEndpoint, upperEndpoint), this.domain)
            : std::make_shared<EmptyContiguousSet>(this.domain));
      }
   }

   public Range<C> range() {
      return this.range(BoundType.CLOSED, BoundType.CLOSED);
   }

   public Range<C> range(BoundType lowerBoundType, BoundType upperBoundType) {
      return Range.create(
         this.range.lowerBound.withLowerBoundType(lowerBoundType, this.domain), this.range.upperBound.withUpperBoundType(upperBoundType, this.domain)
      );
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else {
         if (dynamic_cast<RegularContiguousSet*>(object) != nullptr) {
            RegularContiguousSet<?> that = (RegularContiguousSet<?>)object;
            if (this.domain == that.domain)) {
               return this.first() == that.first()) && this.last() == that.last());
            }
         }

         return super == object);
      }
   }

    int hashCode() {
      return Sets.hashCodeImpl(this);
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.range, this.domain, nullptr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
