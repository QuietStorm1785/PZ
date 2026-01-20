#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/TreeMultiset/AvlNode.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeMultiset {
public:
   AvlNode<E> current;
   Entry<E> prevEntry;

   TreeMultiset$3(TreeMultiset var1) {
      this.this$0 = var1;
      this.current = TreeMultiset.access$1600(this.this$0);
      this.prevEntry = nullptr;
   }

    bool hasNext() {
      if (this.current == nullptr) {
    return false;
      } else if (TreeMultiset.access$1300(this.this$0).tooLow(this.current.getElement())) {
         this.current = nullptr;
    return false;
      } else {
    return true;
      }
   }

   public Entry<E> next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         Entry<E> result = TreeMultiset.access$1400(this.this$0, this.current);
         this.prevEntry = result;
         if (AvlNode.access$1100(this.current) == TreeMultiset.access$1500(this.this$0)) {
            this.current = nullptr;
         } else {
            this.current = AvlNode.access$1100(this.current);
         }

    return result;
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.prevEntry != nullptr);
      this.this$0.setCount(this.prevEntry.getElement(), 0);
      this.prevEntry = nullptr;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
