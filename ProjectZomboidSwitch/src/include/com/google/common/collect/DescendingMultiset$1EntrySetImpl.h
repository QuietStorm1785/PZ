#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/EntrySet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class DescendingMultiset {
public:
   DescendingMultiset$1EntrySetImpl(DescendingMultiset var1) {
      this.this$0 = var1;
   }

   Multiset<E> multiset() {
      return this.this$0;
   }

   public Iterator<Entry<E>> iterator() {
      return this.this$0.entryIterator();
   }

    int size() {
      return this.this$0.forwardMultiset().entrySet().size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
