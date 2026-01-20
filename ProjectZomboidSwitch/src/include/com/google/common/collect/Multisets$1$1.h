#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   Multisets$1$1(1 var1, Iterator var2, Iterator var3) {
      this.this$0 = var1;
      this.val$iterator1 = var2;
      this.val$iterator2 = var3;
   }

   protected Entry<E> computeNext() {
      if (this.val$iterator1.hasNext()) {
         Entry<? : public E> entry1 = (Entry<? : public E>)this.val$iterator1.next();
    E element = (E)entry1.getElement();
    int count = Math.max(entry1.getCount(), this.this$0.val$multiset2.count(element));
         return Multisets.immutableEntry(element, count);
      } else {
         while (this.val$iterator2.hasNext()) {
            Entry<? : public E> entry2 = (Entry<? : public E>)this.val$iterator2.next();
    E element = (E)entry2.getElement();
            if (!this.this$0.val$multiset1.contains(element)) {
               return Multisets.immutableEntry(element, entry2.getCount());
            }
         }

         return (Entry<E>)this.endOfData();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
