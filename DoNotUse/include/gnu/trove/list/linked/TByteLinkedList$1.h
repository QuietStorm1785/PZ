#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/list/linked/TByteLinkedList/TByteLink.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TByteLinkedList {
public:
    TByteLink l;
    TByteLink current;

   TByteLinkedList$1(TByteLinkedList var1) {
      this.this$0 = var1;
      this.l = this.this$0.head;
   }

    uint8_t next() {
      if (TByteLinkedList.no(this.l)) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    uint8_t ret = this.l.getValue();
         this.current = this.l;
         this.l = this.l.getNext();
    return ret;
      }
   }

    bool hasNext() {
      return TByteLinkedList.got(this.l);
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         TByteLinkedList.access$000(this.this$0, this.current);
         this.current = nullptr;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
