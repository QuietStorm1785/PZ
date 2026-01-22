#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/2.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   Multisets$2$1(2 var1, Iterator var2) {
      this.this$0 = var1;
      this.val$iterator1 = var2;
   }

   protected Entry<E> computeNext() {
      while (this.val$iterator1.hasNext()) {
         Entry<E> entry1 = (Entry<E>)this.val$iterator1.next();
    E element = (E)entry1.getElement();
    int count = Math.min(entry1.getCount(), this.this$0.val$multiset2.count(element));
         if (count > 0) {
            return Multisets.immutableEntry(element, count);
         }
      }

      return (Entry<E>)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
