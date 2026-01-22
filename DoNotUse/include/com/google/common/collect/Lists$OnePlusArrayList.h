#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/IntMath.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
    const E first;
   const E[] rest;
    static const long serialVersionUID = 0L;

   Lists$OnePlusArrayList(@Nullable E first, E[] rest) {
      this.first = first;
      this.rest = (E[])((Object[])Preconditions.checkNotNull(rest));
   }

    int size() {
      return IntMath.saturatedAdd(this.rest.length, 1);
   }

    E get(int index) {
      Preconditions.checkElementIndex(index, this.size());
    return index = = 0 ? this.first : this.rest[index - 1];
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
