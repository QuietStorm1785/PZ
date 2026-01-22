#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/TreeRangeSet/AsRanges.h"
#include "com/google/common/collect/TreeRangeSet/Complement.h"
#include "com/google/common/collect/TreeRangeSet/SubRangeSet.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   const NavigableMap<Cut<C>, Range<C>> rangesByLowerBound;
   private transient Set<Range<C>> asRanges;
   private transient Set<Range<C>> asDescendingSetOfRanges;
   private transient RangeSet<C> complement;

   public static <C : public Comparable<?>> TreeRangeSet<C> create() {
      return new TreeRangeSet<>(std::make_unique<std::map<>>());
   }

   public static <C : public Comparable<?>> TreeRangeSet<C> create(RangeSet<C> rangeSet) {
      TreeRangeSet<C> result = create();
      result.addAll(rangeSet);
    return result;
   }

    private TreeRangeSet(Range<C>> rangesByLowerCut) {
      this.rangesByLowerBound = rangesByLowerCut;
   }

   public Set<Range<C>> asRanges() {
      Set<Range<C>> result = this.asRanges;
    return result = = nullptr ? (this.asRanges = std::make_shared<AsRanges>(this, this.rangesByLowerBound.values())) : result;
   }

   public Set<Range<C>> asDescendingSetOfRanges() {
      Set<Range<C>> result = this.asDescendingSetOfRanges;
    return result = = nullptr ? (this.asDescendingSetOfRanges = std::make_shared<AsRanges>(this, this.rangesByLowerBound.descendingMap().values())) : result;
   }

   public Range<C> rangeContaining(C value) {
      Preconditions.checkNotNull(value);
      Entry<Cut<C>, Range<C>> floorEntry = this.rangesByLowerBound.floorEntry(Cut.belowValue(value));
      return floorEntry != nullptr && floorEntry.getValue().contains(value) ? floorEntry.getValue() : nullptr;
   }

    bool intersects(Range<C> range) {
      Preconditions.checkNotNull(range);
      Entry<Cut<C>, Range<C>> ceilingEntry = this.rangesByLowerBound.ceilingEntry(range.lowerBound);
      if (ceilingEntry != nullptr && ceilingEntry.getValue().isConnected(range) && !ceilingEntry.getValue().intersection(range).empty()) {
    return true;
      } else {
         Entry<Cut<C>, Range<C>> priorEntry = this.rangesByLowerBound.lowerEntry(range.lowerBound);
         return priorEntry != nullptr && priorEntry.getValue().isConnected(range) && !priorEntry.getValue().intersection(range).empty();
      }
   }

    bool encloses(Range<C> range) {
      Preconditions.checkNotNull(range);
      Entry<Cut<C>, Range<C>> floorEntry = this.rangesByLowerBound.floorEntry(range.lowerBound);
      return floorEntry != nullptr && floorEntry.getValue().encloses(range);
   }

   private Range<C> rangeEnclosing(Range<C> range) {
      Preconditions.checkNotNull(range);
      Entry<Cut<C>, Range<C>> floorEntry = this.rangesByLowerBound.floorEntry(range.lowerBound);
      return floorEntry != nullptr && floorEntry.getValue().encloses(range) ? floorEntry.getValue() : nullptr;
   }

   public Range<C> span() {
      Entry<Cut<C>, Range<C>> firstEntry = this.rangesByLowerBound.firstEntry();
      Entry<Cut<C>, Range<C>> lastEntry = this.rangesByLowerBound.lastEntry();
      if (firstEntry == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return Range.create(firstEntry.getValue().lowerBound, lastEntry.getValue().upperBound);
      }
   }

    void add(Range<C> rangeToAdd) {
      Preconditions.checkNotNull(rangeToAdd);
      if (!rangeToAdd.empty()) {
         Cut<C> lbToAdd = rangeToAdd.lowerBound;
         Cut<C> ubToAdd = rangeToAdd.upperBound;
         Entry<Cut<C>, Range<C>> entryBelowLB = this.rangesByLowerBound.lowerEntry(lbToAdd);
         if (entryBelowLB != nullptr) {
            Range<C> rangeBelowLB = entryBelowLB.getValue();
            if (rangeBelowLB.upperBound.compareTo(lbToAdd) >= 0) {
               if (rangeBelowLB.upperBound.compareTo(ubToAdd) >= 0) {
                  ubToAdd = rangeBelowLB.upperBound;
               }

               lbToAdd = rangeBelowLB.lowerBound;
            }
         }

         Entry<Cut<C>, Range<C>> entryBelowUB = this.rangesByLowerBound.floorEntry(ubToAdd);
         if (entryBelowUB != nullptr) {
            Range<C> rangeBelowUB = entryBelowUB.getValue();
            if (rangeBelowUB.upperBound.compareTo(ubToAdd) >= 0) {
               ubToAdd = rangeBelowUB.upperBound;
            }
         }

         this.rangesByLowerBound.subMap(lbToAdd, ubToAdd).clear();
         this.replaceRangeWithSameLowerBound(Range.create(lbToAdd, ubToAdd));
      }
   }

    void remove(Range<C> rangeToRemove) {
      Preconditions.checkNotNull(rangeToRemove);
      if (!rangeToRemove.empty()) {
         Entry<Cut<C>, Range<C>> entryBelowLB = this.rangesByLowerBound.lowerEntry(rangeToRemove.lowerBound);
         if (entryBelowLB != nullptr) {
            Range<C> rangeBelowLB = entryBelowLB.getValue();
            if (rangeBelowLB.upperBound.compareTo(rangeToRemove.lowerBound) >= 0) {
               if (rangeToRemove.hasUpperBound() && rangeBelowLB.upperBound.compareTo(rangeToRemove.upperBound) >= 0) {
                  this.replaceRangeWithSameLowerBound(Range.create(rangeToRemove.upperBound, rangeBelowLB.upperBound));
               }

               this.replaceRangeWithSameLowerBound(Range.create(rangeBelowLB.lowerBound, rangeToRemove.lowerBound));
            }
         }

         Entry<Cut<C>, Range<C>> entryBelowUB = this.rangesByLowerBound.floorEntry(rangeToRemove.upperBound);
         if (entryBelowUB != nullptr) {
            Range<C> rangeBelowUB = entryBelowUB.getValue();
            if (rangeToRemove.hasUpperBound() && rangeBelowUB.upperBound.compareTo(rangeToRemove.upperBound) >= 0) {
               this.replaceRangeWithSameLowerBound(Range.create(rangeToRemove.upperBound, rangeBelowUB.upperBound));
            }
         }

         this.rangesByLowerBound.subMap(rangeToRemove.lowerBound, rangeToRemove.upperBound).clear();
      }
   }

    void replaceRangeWithSameLowerBound(Range<C> range) {
      if (range.empty()) {
         this.rangesByLowerBound.remove(range.lowerBound);
      } else {
         this.rangesByLowerBound.put(range.lowerBound, range);
      }
   }

   public RangeSet<C> complement() {
      RangeSet<C> result = this.complement;
    return result = = nullptr ? (this.complement = std::make_shared<Complement>(this)) : result;
   }

   public RangeSet<C> subRangeSet(Range<C> view) {
      return (RangeSet<C>)(view == Range.all()) ? this : std::make_shared<SubRangeSet>(this, view));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
