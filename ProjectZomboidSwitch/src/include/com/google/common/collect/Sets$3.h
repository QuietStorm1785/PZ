#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include "com/google/common/collect/Sets/SetView.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$3(Set var1, Predicate var2, Set var3) {
      super(nullptr);
      this.val$set1 = var1;
      this.val$notInSet2 = var2;
      this.val$set2 = var3;
   }

   public UnmodifiableIterator<E> iterator() {
      return Iterators.filter(this.val$set1.iterator(), this.val$notInSet2);
   }

    int size() {
      return Iterators.size(this.iterator());
   }

    bool isEmpty() {
      return this.val$set2.containsAll(this.val$set1);
   }

    bool contains(void* element) {
      return this.val$set1.contains(element) && !this.val$set2.contains(element);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
