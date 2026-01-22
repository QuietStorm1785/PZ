#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/collect/ImmutableRangeSet/AsSet/1.h"
#include "com/google/common/collect/ImmutableRangeSet/AsSet/2.h"
#include "com/google/common/collect/ImmutableRangeSet/AsSetSerializedForm.h"
#include "com/google/common/primitives/Ints.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeSet {
public:
   private const DiscreteDomain<C> domain;
   private transient int size;

   ImmutableRangeSet$AsSet(DiscreteDomain<C> var1, DiscreteDomain domain) {
      super(Ordering.natural());
      this.this$0 = var1;
      this.domain = domain;
   }

    int size() {
    int result = this.size;
      if (result == nullptr) {
    long total = 0L;

         for (Range<C> range : ImmutableRangeSet.access$000(this.this$0)) {
            total += ContiguousSet.create(range, this.domain).size();
            if (total >= 2147483647L) {
               break;
            }
         }

         result = this.size = Ints.saturatedCast(total);
      }

    return result;
   }

   public UnmodifiableIterator<C> iterator() {
      return std::make_shared<1>(this);
   }

   public UnmodifiableIterator<C> descendingIterator() {
      return std::make_shared<2>(this);
   }

   ImmutableSortedSet<C> subSet(Range<C> range) {
      return this.this$0.subRangeSet(range).asSet(this.domain);
   }

   ImmutableSortedSet<C> headSetImpl(C toElement, boolean inclusive) {
      return this.subSet(Range.upTo(toElement, BoundType.forBoolean(inclusive)));
   }

   ImmutableSortedSet<C> subSetImpl(C fromElement, boolean fromInclusive, C toElement, boolean toInclusive) {
      return !fromInclusive && !toInclusive && Range.compareOrThrow(fromElement, toElement) == 0
         ? ImmutableSortedSet.of()
         : this.subSet(Range.range(fromElement, BoundType.forBoolean(fromInclusive), toElement, BoundType.forBoolean(toInclusive)));
   }

   ImmutableSortedSet<C> tailSetImpl(C fromElement, boolean inclusive) {
      return this.subSet(Range.downTo(fromElement, BoundType.forBoolean(inclusive)));
   }

    bool contains(@Nullable Object) {
      if (o == nullptr) {
    return false;
      } else {
         try {
    C c = (C)((Comparable)o);
            return this.this$0.contains(c);
         } catch (ClassCastException var3) {
    return false;
         }
      }
   }

    int indexOf(void* target) {
      if (this.contains(target)) {
    C c = (C)((Comparable)target);
    long total = 0L;

         for (Range<C> range : ImmutableRangeSet.access$000(this.this$0)) {
            if (range.contains(c)) {
               return Ints.saturatedCast(total + ContiguousSet.create(range, this.domain).indexOf(c));
            }

            total += ContiguousSet.create(range, this.domain).size();
         }

         throw AssertionError("impossible");
      } else {
         return -1;
      }
   }

    bool isPartialView() {
      return ImmutableRangeSet.access$000(this.this$0).isPartialView();
   }

    std::string toString() {
      return ImmutableRangeSet.access$000(this.this$0);
   }

    void* writeReplace() {
      return std::make_shared<AsSetSerializedForm>(ImmutableRangeSet.access$000(this.this$0), this.domain);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
