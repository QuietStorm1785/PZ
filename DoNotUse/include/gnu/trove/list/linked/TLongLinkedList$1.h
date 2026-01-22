#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/list/linked/TLongLinkedList/TLongLink.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TLongLinkedList {
public:
    TLongLink l;
    TLongLink current;

   TLongLinkedList$1(TLongLinkedList var1) {
      this.this$0 = var1;
      this.l = this.this$0.head;
   }

    long next() {
      if (TLongLinkedList.no(this.l)) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    long ret = this.l.getValue();
         this.current = this.l;
         this.l = this.l.getNext();
    return ret;
      }
   }

    bool hasNext() {
      return TLongLinkedList.got(this.l);
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         TLongLinkedList.access$000(this.this$0, this.current);
         this.current = nullptr;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
