#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/4/1.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   Multisets$4(Multiset var1, Multiset var2) {
      this.val$multiset1 = var1;
      this.val$multiset2 = var2;
   }

    int count(@Nullable Object) {
    int count1 = this.val$multiset1.count(element);
    return count1 = = 0 ? 0 : Math.max(0, count1 - this.val$multiset2.count(element));
   }

   Iterator<Entry<E>> entryIterator() {
      Iterator<Entry<E>> iterator1 = this.val$multiset1.entrySet().iterator();
      return std::make_shared<1>(this, iterator1);
   }

    int distinctElements() {
      return Iterators.size(this.entryIterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
