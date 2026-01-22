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


class AbstractSortedMultiset {
public:
   AbstractSortedMultiset$1DescendingMultisetImpl(AbstractSortedMultiset var1) {
      this.this$0 = var1;
   }

   SortedMultiset<E> forwardMultiset() {
      return this.this$0;
   }

   Iterator<Entry<E>> entryIterator() {
      return this.this$0.descendingEntryIterator();
   }

   public Iterator<E> iterator() {
      return this.this$0.descendingIterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
