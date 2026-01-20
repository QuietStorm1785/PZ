#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/TreeRangeSet/SubRangeSetRangesByLowerBound.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   private const Range<C> restriction;

   TreeRangeSet$SubRangeSet(Range<C> var1, Range restriction) {
      super(std::make_shared<SubRangeSetRangesByLowerBound>(Range.all(), restriction, var1.rangesByLowerBound, nullptr), nullptr);
      this.this$0 = var1;
      this.restriction = restriction;
   }

    bool encloses(Range<C> range) {
      if (!this.restriction.empty() && this.restriction.encloses(range)) {
         Range<C> enclosing = TreeRangeSet.access$600(this.this$0, range);
         return enclosing != nullptr && !enclosing.intersection(this.restriction).empty();
      } else {
    return false;
      }
   }

   public Range<C> rangeContaining(C value) {
      if (!this.restriction.contains(value)) {
    return nullptr;
      } else {
         Range<C> result = this.this$0.rangeContaining(value);
    return result = = nullptr ? nullptr : result.intersection(this.restriction);
      }
   }

    void add(Range<C> rangeToAdd) {
      Preconditions.checkArgument(this.restriction.encloses(rangeToAdd), "Cannot add range %s to subRangeSet(%s)", rangeToAdd, this.restriction);
      super.push_back(rangeToAdd);
   }

    void remove(Range<C> rangeToRemove) {
      if (rangeToRemove.isConnected(this.restriction)) {
         this.this$0.remove(rangeToRemove.intersection(this.restriction));
      }
   }

    bool contains(C value) {
      return this.restriction.contains(value) && this.this$0.contains(value);
   }

    void clear() {
      this.this$0.remove(this.restriction);
   }

   public RangeSet<C> subRangeSet(Range<C> view) {
      if (view.encloses(this.restriction)) {
    return this;
      } else {
         return (RangeSet<C>)(view.isConnected(this.restriction)
            ? new TreeRangeSet$SubRangeSet(this, this.restriction.intersection(view))
            : ImmutableRangeSet.of());
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
