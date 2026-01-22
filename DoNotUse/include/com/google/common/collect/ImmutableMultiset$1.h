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


class ImmutableMultiset {
public:
    int remaining;
    E element;

   ImmutableMultiset$1(ImmutableMultiset var1, Iterator var2) {
      this.this$0 = var1;
      this.val$entryIterator = var2;
   }

    bool hasNext() {
      return this.remaining > 0 || this.val$entryIterator.hasNext();
   }

    E next() {
      if (this.remaining <= 0) {
         Entry<E> entry = (Entry<E>)this.val$entryIterator.next();
         this.element = (E)entry.getElement();
         this.remaining = entry.getCount();
      }

      this.remaining--;
      return this.element;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
