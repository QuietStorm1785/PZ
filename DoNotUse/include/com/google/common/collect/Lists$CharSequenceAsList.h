#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
    const CharSequence sequence;

   Lists$CharSequenceAsList(CharSequence sequence) {
      this.sequence = sequence;
   }

    char get(int index) {
      Preconditions.checkElementIndex(index, this.size());
      return this.sequence.charAt(index);
   }

    int size() {
      return this.sequence.length();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
