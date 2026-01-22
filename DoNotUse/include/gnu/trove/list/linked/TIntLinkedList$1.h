#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/list/linked/TIntLinkedList/TIntLink.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TIntLinkedList {
public:
    TIntLink l;
    TIntLink current;

   TIntLinkedList$1(TIntLinkedList var1) {
      this.this$0 = var1;
      this.l = this.this$0.head;
   }

    int next() {
      if (TIntLinkedList.no(this.l)) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    int ret = this.l.getValue();
         this.current = this.l;
         this.l = this.l.getNext();
    return ret;
      }
   }

    bool hasNext() {
      return TIntLinkedList.got(this.l);
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         TIntLinkedList.access$000(this.this$0, this.current);
         this.current = nullptr;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
