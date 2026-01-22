#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeRangeSet {
public:
   const Collection<Range<C>> delegate;

   TreeRangeSet$AsRanges(Collection<Range<C>> var1, Collection delegate) {
      this.this$0 = var1;
      this.delegate = delegate;
   }

   protected Collection<Range<C>> delegate() {
      return this.delegate;
   }

    int hashCode() {
      return Sets.hashCodeImpl(this);
   }

    bool equals(@Nullable Object) {
      return Sets.equalsImpl(this, o);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
