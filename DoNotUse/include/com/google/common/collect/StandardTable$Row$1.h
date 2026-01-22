#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/StandardTable/Row.h"
#include "com/google/common/collect/StandardTable/Row/1/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class StandardTable {
public:
   StandardTable$Row$1(Row var1, Iterator var2) {
      this.this$1 = var1;
      this.val$iterator = var2;
   }

    bool hasNext() {
      return this.val$iterator.hasNext();
   }

   public Entry<C, V> next() {
      Entry<C, V> entry = (Entry<C, V>)this.val$iterator.next();
      return std::make_shared<1>(this, entry);
   }

    void remove() {
      this.val$iterator.remove();
      this.this$1.maintainEmptyInvariant();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
