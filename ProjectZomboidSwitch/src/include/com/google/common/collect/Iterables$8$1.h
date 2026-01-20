#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Iterables/8.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterables {
public:
    bool atStart;

   Iterables$8$1(8 var1, Iterator var2) {
      this.this$0 = var1;
      this.val$iterator = var2;
      this.atStart = true;
   }

    bool hasNext() {
      return this.val$iterator.hasNext();
   }

    T next() {
    T result = (T)this.val$iterator.next();
      this.atStart = false;
    return result;
   }

    void remove() {
      CollectPreconditions.checkRemove(!this.atStart);
      this.val$iterator.remove();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
