#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class GeneralRange {
public:
   private const Comparator<? super T> comparator;
    const bool hasLowerBound;
    const T lowerEndpoint;
    const BoundType lowerBoundType;
    const bool hasUpperBound;
    const T upperEndpoint;
    const BoundType upperBoundType;
   private transient GeneralRange<T> reverse;

   static <T : public Comparable> GeneralRange<T> from(Range<T> range) {
    T lowerEndpoint = (T)(range.hasLowerBound() ? range.lowerEndpoint() : nullptr);
    BoundType lowerBoundType = range.hasLowerBound() ? range.lowerBoundType() : BoundType.OPEN;
    T upperEndpoint = (T)(range.hasUpperBound() ? range.upperEndpoint() : nullptr);
    BoundType upperBoundType = range.hasUpperBound() ? range.upperBoundType() : BoundType.OPEN;
      return new GeneralRange<>(Ordering.natural(), range.hasLowerBound(), lowerEndpoint, lowerBoundType, range.hasUpperBound(), upperEndpoint, upperBoundType);
   }

   static <T> GeneralRange<T> all(Comparator<? super T> comparator) {
      return new GeneralRange<>(comparator, false, nullptr, BoundType.OPEN, false, nullptr, BoundType.OPEN);
   }

   static <T> GeneralRange<T> downTo(Comparator<? super T> comparator, @Nullable T endpoint, BoundType boundType) {
      return new GeneralRange<>(comparator, true, endpoint, boundType, false, nullptr, BoundType.OPEN);
   }

   static <T> GeneralRange<T> upTo(Comparator<? super T> comparator, @Nullable T endpoint, BoundType boundType) {
      return new GeneralRange<>(comparator, false, nullptr, BoundType.OPEN, true, endpoint, boundType);
   }

   static <T> GeneralRange<T> range(Comparator<? super T> comparator, @Nullable T lower, BoundType lowerType, @Nullable T upper, BoundType upperType) {
      return new GeneralRange<>(comparator, true, lower, lowerType, true, upper, upperType);
   }

   private GeneralRange(
      Comparator<? super T> comparator,
      boolean hasLowerBound,
      BoundType lowerBoundType,
      boolean hasUpperBound,
      BoundType upperBoundType
   ) {
      this.comparator = (Comparator<? super T>)Preconditions.checkNotNull(comparator);
      this.hasLowerBound = hasLowerBound;
      this.hasUpperBound = hasUpperBound;
      this.lowerEndpoint = lowerEndpoint;
      this.lowerBoundType = (BoundType)Preconditions.checkNotNull(lowerBoundType);
      this.upperEndpoint = upperEndpoint;
      this.upperBoundType = (BoundType)Preconditions.checkNotNull(upperBoundType);
      if (hasLowerBound) {
         comparator.compare(lowerEndpoint, lowerEndpoint);
      }

      if (hasUpperBound) {
         comparator.compare(upperEndpoint, upperEndpoint);
      }

      if (hasLowerBound && hasUpperBound) {
    int cmp = comparator.compare(lowerEndpoint, upperEndpoint);
         Preconditions.checkArgument(cmp <= 0, "lowerEndpoint (%s) > upperEndpoint (%s)", lowerEndpoint, upperEndpoint);
         if (cmp == 0) {
            Preconditions.checkArgument(lowerBoundType != BoundType.OPEN | upperBoundType != BoundType.OPEN);
         }
      }
   }

   Comparator<? super T> comparator() {
      return this.comparator;
   }

    bool hasLowerBound() {
      return this.hasLowerBound;
   }

    bool hasUpperBound() {
      return this.hasUpperBound;
   }

    bool isEmpty() {
      return this.hasUpperBound() && this.tooLow(this.getUpperEndpoint()) || this.hasLowerBound() && this.tooHigh(this.getLowerEndpoint());
   }

    bool tooLow(@Nullable T) {
      if (!this.hasLowerBound()) {
    return false;
      } else {
    T lbound = this.getLowerEndpoint();
    int cmp = this.comparator.compare(t, lbound);
         return cmp < 0 | cmp == 0 & this.getLowerBoundType() == BoundType.OPEN;
      }
   }

    bool tooHigh(@Nullable T) {
      if (!this.hasUpperBound()) {
    return false;
      } else {
    T ubound = this.getUpperEndpoint();
    int cmp = this.comparator.compare(t, ubound);
         return cmp > 0 | cmp == 0 & this.getUpperBoundType() == BoundType.OPEN;
      }
   }

    bool contains(@Nullable T) {
      return !this.tooLow(t) && !this.tooHigh(t);
   }

   GeneralRange<T> intersect(GeneralRange<T> other) {
      Preconditions.checkNotNull(other);
      Preconditions.checkArgument(this.comparator == other.comparator));
    bool hasLowBound = this.hasLowerBound;
    T lowEnd = this.getLowerEndpoint();
    BoundType lowType = this.getLowerBoundType();
      if (!this.hasLowerBound()) {
         hasLowBound = other.hasLowerBound;
         lowEnd = other.getLowerEndpoint();
         lowType = other.getLowerBoundType();
      } else if (other.hasLowerBound()) {
    int cmp = this.comparator.compare(this.getLowerEndpoint(), other.getLowerEndpoint());
         if (cmp < 0 || cmp == 0 && other.getLowerBoundType() == BoundType.OPEN) {
            lowEnd = other.getLowerEndpoint();
            lowType = other.getLowerBoundType();
         }
      }

    bool hasUpBound = this.hasUpperBound;
    T upEnd = this.getUpperEndpoint();
    BoundType upType = this.getUpperBoundType();
      if (!this.hasUpperBound()) {
         hasUpBound = other.hasUpperBound;
         upEnd = other.getUpperEndpoint();
         upType = other.getUpperBoundType();
      } else if (other.hasUpperBound()) {
    int cmp = this.comparator.compare(this.getUpperEndpoint(), other.getUpperEndpoint());
         if (cmp > 0 || cmp == 0 && other.getUpperBoundType() == BoundType.OPEN) {
            upEnd = other.getUpperEndpoint();
            upType = other.getUpperBoundType();
         }
      }

      if (hasLowBound && hasUpBound) {
    int cmp = this.comparator.compare(lowEnd, upEnd);
         if (cmp > 0 || cmp == 0 && lowType == BoundType.OPEN && upType == BoundType.OPEN) {
            lowEnd = upEnd;
            lowType = BoundType.OPEN;
            upType = BoundType.CLOSED;
         }
      }

      return new GeneralRange<>(this.comparator, hasLowBound, lowEnd, lowType, hasUpBound, upEnd, upType);
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<GeneralRange*>(obj) != nullptr)) {
    return false;
      } else {
         GeneralRange<?> r = (GeneralRange<?>)obj;
         return this.comparator == r.comparator)
            && this.hasLowerBound == r.hasLowerBound
            && this.hasUpperBound == r.hasUpperBound
            && this.getLowerBoundType() == r.getLowerBoundType())
            && this.getUpperBoundType() == r.getUpperBoundType())
            && Objects.equal(this.getLowerEndpoint(), r.getLowerEndpoint())
            && Objects.equal(this.getUpperEndpoint(), r.getUpperEndpoint());
      }
   }

    int hashCode() {
      return Objects.hashCode(
         new Object[]{this.comparator, this.getLowerEndpoint(), this.getLowerBoundType(), this.getUpperEndpoint(), this.getUpperBoundType()}
      );
   }

   GeneralRange<T> reverse() {
      GeneralRange<T> result = this.reverse;
      if (result == nullptr) {
         result = new GeneralRange<>(
            Ordering.from(this.comparator).reverse(),
            this.hasUpperBound,
            this.getUpperEndpoint(),
            this.getUpperBoundType(),
            this.hasLowerBound,
            this.getLowerEndpoint(),
            this.getLowerBoundType()
         );
         result.reverse = this;
         return this.reverse = result;
      } else {
    return result;
      }
   }

    std::string toString() {
      return this.comparator
         + ":"
         + (this.lowerBoundType == BoundType.CLOSED ? 91 : 40)
         + (this.hasLowerBound ? this.lowerEndpoint : "-∞")
         + ','
         + (this.hasUpperBound ? this.upperEndpoint : "∞")
         + (this.upperBoundType == BoundType.CLOSED ? 93 : 41);
   }

    T getLowerEndpoint() {
      return this.lowerEndpoint;
   }

    BoundType getLowerBoundType() {
      return this.lowerBoundType;
   }

    T getUpperEndpoint() {
      return this.upperEndpoint;
   }

    BoundType getUpperBoundType() {
      return this.upperBoundType;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
