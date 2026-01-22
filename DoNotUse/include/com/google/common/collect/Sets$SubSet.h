#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets/SubSet/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   private const ImmutableMap<E, int> inputSet;
    const int mask;

   Sets$SubSet(ImmutableMap<E, int> inputSet, int mask) {
      this.inputSet = inputSet;
      this.mask = mask;
   }

   public Iterator<E> iterator() {
      return std::make_shared<1>(this);
   }

    int size() {
      return int.bitCount(this.mask);
   }

    bool contains(@Nullable Object) {
    int index = (int)this.inputSet.get(o);
      return index != nullptr && (this.mask & 1 << index) != 0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
