#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TCharIterator.h"
#include "gnu/trove/list/linked/TCharLinkedList/TCharLink.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TCharLinkedList {
public:
    TCharLink l;
    TCharLink current;

   TCharLinkedList$1(TCharLinkedList var1) {
      this.this$0 = var1;
      this.l = this.this$0.head;
   }

    char next() {
      if (TCharLinkedList.no(this.l)) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    char ret = this.l.getValue();
         this.current = this.l;
         this.l = this.l.getNext();
    return ret;
      }
   }

    bool hasNext() {
      return TCharLinkedList.got(this.l);
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         TCharLinkedList.access$000(this.this$0, this.current);
         this.current = nullptr;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
