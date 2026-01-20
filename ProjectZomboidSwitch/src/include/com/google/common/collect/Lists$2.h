#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Lists/AbstractListWrapper.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
    static const long serialVersionUID = 0L;

   Lists$2(List x0) {
      super(x0);
   }

   public ListIterator<E> listIterator(int index) {
      return this.backingList.listIterator(index);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
