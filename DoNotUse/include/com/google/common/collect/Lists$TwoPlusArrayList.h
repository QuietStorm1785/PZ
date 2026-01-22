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
    const E second;
   const E[] rest;
    static const long serialVersionUID = 0L;

   Lists$TwoPlusArrayList(@Nullable E first, @Nullable E second, E[] rest) {
      this.first = first;
      this.second = second;
      this.rest = (E[])((Object[])Preconditions.checkNotNull(rest));
   }

    int size() {
      return IntMath.saturatedAdd(this.rest.length, 2);
   }

    E get(int index) {
      switch (index) {
         case 0:
            return this.first;
         case 1:
            return this.second;
         default:
            Preconditions.checkElementIndex(index, this.size());
            return this.rest[index - 2];
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
