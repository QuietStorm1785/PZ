#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSet/Indexed.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RegularImmutableMultiset {
public:
   private RegularImmutableMultiset$ElementSet(RegularImmutableMultiset var1) {
      this.this$0 = var1;
   }

    E get(int index) {
      return (E)RegularImmutableMultiset.access$100(this.this$0)[index].getElement();
   }

    bool contains(@Nullable Object) {
      return this.this$0.contains(object);
   }

    bool isPartialView() {
    return true;
   }

    int size() {
      return RegularImmutableMultiset.access$100(this.this$0).length;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
