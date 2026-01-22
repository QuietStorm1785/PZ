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
   Sets$2(Set var1, Predicate var2, Set var3) {
      super(nullptr);
      this.val$set1 = var1;
      this.val$inSet2 = var2;
      this.val$set2 = var3;
   }

   public UnmodifiableIterator<E> iterator() {
      return Iterators.filter(this.val$set1.iterator(), this.val$inSet2);
   }

    int size() {
      return Iterators.size(this.iterator());
   }

    bool isEmpty() {
      return !this.iterator().hasNext();
   }

    bool contains(void* object) {
      return this.val$set1.contains(object) && this.val$set2.contains(object);
   }

    bool containsAll(Collection<?> collection) {
      return this.val$set1.containsAll(collection) && this.val$set2.containsAll(collection);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
