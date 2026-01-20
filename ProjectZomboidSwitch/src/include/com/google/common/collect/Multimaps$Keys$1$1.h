#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/Keys/1.h"
#include "com/google/common/collect/Multisets/AbstractEntry.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$Keys$1$1(1 var1, Entry var2) {
      this.this$1 = var1;
      this.val$backingEntry = var2;
   }

    K getElement() {
      return (K)this.val$backingEntry.getKey();
   }

    int getCount() {
      return ((Collection)this.val$backingEntry.getValue()).size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
