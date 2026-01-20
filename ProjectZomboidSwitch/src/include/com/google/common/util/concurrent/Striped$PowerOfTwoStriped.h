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
namespace util {
namespace concurrent {


class Striped {
public:
    const int mask;

   Striped$PowerOfTwoStriped(int stripes) {
      super(nullptr);
      Preconditions.checkArgument(stripes > 0, "Stripes must be positive");
      this.mask = stripes > 1073741824 ? -1 : Striped.access$200(stripes) - 1;
   }

    int indexFor(void* key) {
    int hash = Striped.access$300(key.hashCode());
      return hash & this.mask;
   }

    L get(void* key) {
      return (L)this.getAt(this.indexFor(key));
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
