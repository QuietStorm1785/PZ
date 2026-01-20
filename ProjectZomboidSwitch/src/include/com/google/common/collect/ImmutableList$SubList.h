#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableList {
public:
   const transient int offset;
   const transient int length;

   ImmutableList$SubList(ImmutableList var1, int offset, int length) {
      this.this$0 = var1;
      this.offset = offset;
      this.length = length;
   }

    int size() {
      return this.length;
   }

    E get(int index) {
      Preconditions.checkElementIndex(index, this.length);
      return (E)this.this$0.get(index + this.offset);
   }

   public ImmutableList<E> subList(int fromIndex, int toIndex) {
      Preconditions.checkPositionIndexes(fromIndex, toIndex, this.length);
      return this.this$0.subList(fromIndex + this.offset, toIndex + this.offset);
   }

    bool isPartialView() {
    return true;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
