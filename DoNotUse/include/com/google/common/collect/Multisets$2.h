#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/Multisets/2/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multisets {
public:
   Multisets$2(Multiset var1, Multiset var2) {
      this.val$multiset1 = var1;
      this.val$multiset2 = var2;
   }

    int count(void* element) {
    int count1 = this.val$multiset1.count(element);
    return count1 = = 0 ? 0 : Math.min(count1, this.val$multiset2.count(element));
   }

   Set<E> createElementSet() {
      return Sets.intersection(this.val$multiset1.elementSet(), this.val$multiset2.elementSet());
   }

   Iterator<Entry<E>> entryIterator() {
      Iterator<Entry<E>> iterator1 = this.val$multiset1.entrySet().iterator();
      return std::make_shared<1>(this, iterator1);
   }

    int distinctElements() {
      return this.elementSet().size();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
