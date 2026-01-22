#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TFloatIterator.h"
#include "gnu/trove/list/linked/TFloatLinkedList/TFloatLink.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TFloatLinkedList {
public:
    TFloatLink l;
    TFloatLink current;

   TFloatLinkedList$1(TFloatLinkedList var1) {
      this.this$0 = var1;
      this.l = this.this$0.head;
   }

    float next() {
      if (TFloatLinkedList.no(this.l)) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    float ret = this.l.getValue();
         this.current = this.l;
         this.l = this.l.getNext();
    return ret;
      }
   }

    bool hasNext() {
      return TFloatLinkedList.got(this.l);
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         TFloatLinkedList.access$000(this.this$0, this.current);
         this.current = nullptr;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
