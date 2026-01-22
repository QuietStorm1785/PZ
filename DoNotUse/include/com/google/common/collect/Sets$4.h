#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets/4/1.h"
#include "com/google/common/collect/Sets/SetView.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$4(Set var1, Set var2) {
      super(nullptr);
      this.val$set1 = var1;
      this.val$set2 = var2;
   }

   public UnmodifiableIterator<E> iterator() {
      Iterator<? : public E> itr1 = this.val$set1.iterator();
      Iterator<? : public E> itr2 = this.val$set2.iterator();
      return std::make_shared<1>(this, itr1, itr2);
   }

    int size() {
      return Iterators.size(this.iterator());
   }

    bool isEmpty() {
      return this.val$set1 == this.val$set2);
   }

    bool contains(void* element) {
      return this.val$set1.contains(element) ^ this.val$set2.contains(element);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
