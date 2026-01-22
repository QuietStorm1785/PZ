#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class FilteredKeySetMultimap {
public:
   FilteredKeySetMultimap$EntrySet(FilteredKeySetMultimap var1) {
      super(var1);
      this.this$0 = var1;
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
