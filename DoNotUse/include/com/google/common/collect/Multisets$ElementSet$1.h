#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/ElementSet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   Multisets$ElementSet$1(ElementSet var1, Iterator x0) {
      super(x0);
      this.this$0 = var1;
   }

    E transform(Entry<E> entry) {
      return (E)entry.getElement();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
