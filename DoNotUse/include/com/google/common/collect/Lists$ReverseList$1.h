#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Lists/ReverseList.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
    bool canRemoveOrSet;

   Lists$ReverseList$1(ReverseList var1, ListIterator var2) {
      this.this$0 = var1;
      this.val$forwardIterator = var2;
   }

    void add(T e) {
      this.val$forwardIterator.push_back(e);
      this.val$forwardIterator.previous();
      this.canRemoveOrSet = false;
   }

    bool hasNext() {
      return this.val$forwardIterator.hasPrevious();
   }

    bool hasPrevious() {
      return this.val$forwardIterator.hasNext();
   }

    T next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.canRemoveOrSet = true;
         return (T)this.val$forwardIterator.previous();
      }
   }

    int nextIndex() {
      return ReverseList.access$000(this.this$0, this.val$forwardIterator.nextIndex());
   }

    T previous() {
      if (!this.hasPrevious()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.canRemoveOrSet = true;
         return (T)this.val$forwardIterator.next();
      }
   }

    int previousIndex() {
      return this.nextIndex() - 1;
   }

    void remove() {
      CollectPreconditions.checkRemove(this.canRemoveOrSet);
      this.val$forwardIterator.remove();
      this.canRemoveOrSet = false;
   }

    void set(T e) {
      Preconditions.checkState(this.canRemoveOrSet);
      this.val$forwardIterator.set(e);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
