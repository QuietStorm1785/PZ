#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/util/concurrent/Striped/PowerOfTwoStriped.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Striped {
public:
   private const Object[] array;

   private Striped$CompactStriped(int stripes, Supplier<L> supplier) {
      super(stripes);
      Preconditions.checkArgument(stripes <= 1073741824, "Stripes must be <= 2^30)");
      this.array = new Object[this.mask + 1];

      for (int i = 0; i < this.array.length; i++) {
         this.array[i] = supplier.get();
      }
   }

    L getAt(int index) {
      return (L)this.array[index];
   }

    int size() {
      return this.array.length;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
