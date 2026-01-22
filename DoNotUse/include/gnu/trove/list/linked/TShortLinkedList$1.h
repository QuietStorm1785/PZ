#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortIterator.h"
#include "gnu/trove/list/linked/TShortLinkedList/TShortLink.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TShortLinkedList {
public:
    TShortLink l;
    TShortLink current;

   TShortLinkedList$1(TShortLinkedList var1) {
      this.this$0 = var1;
      this.l = this.this$0.head;
   }

    short next() {
      if (TShortLinkedList.no(this.l)) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    short ret = this.l.getValue();
         this.current = this.l;
         this.l = this.l.getNext();
    return ret;
      }
   }

    bool hasNext() {
      return TShortLinkedList.got(this.l);
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         TShortLinkedList.access$000(this.this$0, this.current);
         this.current = nullptr;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
