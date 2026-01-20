#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/collect/MapMaker.h"
#include "com/google/common/util/concurrent/Striped/PowerOfTwoStriped.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Striped {
public:
   const ConcurrentMap<int, L> locks;
   const Supplier<L> supplier;
    const int size = this.mask == -1 ? int.MAX_VALUE : this.mask + 1;

   Striped$LargeLazyStriped(int stripes, Supplier<L> supplier) {
      super(stripes);
      this.supplier = supplier;
      this.locks = std::make_unique<MapMaker>().weakValues().makeMap();
   }

    L getAt(int index) {
      if (this.size != int.MAX_VALUE) {
         Preconditions.checkElementIndex(index, this.size());
      }

    L existing = this.locks.get(index);
      if (existing != nullptr) {
    return existing;
      } else {
    L created = (L)this.supplier.get();
         existing = this.locks.putIfAbsent(index, created);
         return (L)MoreObjects.firstNonNull(existing, created);
      }
   }

    int size() {
      return this.size;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
