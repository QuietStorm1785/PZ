#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ConcurrentHashMultiset {
public:
   private Entry<E> last;

   ConcurrentHashMultiset$3(ConcurrentHashMultiset var1, Iterator var2) {
      this.this$0 = var1;
      this.val$readOnlyIterator = var2;
   }

   protected Iterator<Entry<E>> delegate() {
      return this.val$readOnlyIterator;
   }

   public Entry<E> next() {
      this.last = (Entry<E>)super.next();
      return this.last;
   }

    void remove() {
      CollectPreconditions.checkRemove(this.last != nullptr);
      this.this$0.setCount(this.last.getElement(), 0);
      this.last = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
