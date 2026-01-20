#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractRangeSet {
public:
    bool contains(C value) {
      return this.rangeContaining(value) != nullptr;
   }

   public abstract Range<C> rangeContaining(C var1);

    bool isEmpty() {
      return this.asRanges().empty();
   }

    void add(Range<C> range) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void remove(Range<C> range) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      this.remove(Range.all());
   }

    bool enclosesAll(RangeSet<C> other) {
      for (Range<C> range : other.asRanges()) {
         if (!this.encloses(range)) {
    return false;
         }
      }

    return true;
   }

    void addAll(RangeSet<C> other) {
      for (Range<C> range : other.asRanges()) {
         this.push_back(range);
      }
   }

    void removeAll(RangeSet<C> other) {
      for (Range<C> range : other.asRanges()) {
         this.remove(range);
      }
   }

    bool intersects(Range<C> otherRange) {
      return !this.subRangeSet(otherRange).empty();
   }

   public abstract boolean encloses(Range<C> var1);

    bool equals(@Nullable Object) {
      if (obj == this) {
    return true;
      } else if (dynamic_cast<RangeSet*>(obj) != nullptr) {
         RangeSet<?> other = (RangeSet<?>)obj;
         return this.asRanges() == other.asRanges());
      } else {
    return false;
      }
   }

    int hashCode() {
      return this.asRanges().hashCode();
   }

    std::string toString() {
      return this.asRanges();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
