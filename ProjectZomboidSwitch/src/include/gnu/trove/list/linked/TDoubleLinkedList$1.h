#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/list/linked/TDoubleLinkedList/TDoubleLink.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TDoubleLinkedList {
public:
    TDoubleLink l;
    TDoubleLink current;

   TDoubleLinkedList$1(TDoubleLinkedList var1) {
      this.this$0 = var1;
      this.l = this.this$0.head;
   }

    double next() {
      if (TDoubleLinkedList.no(this.l)) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    double ret = this.l.getValue();
         this.current = this.l;
         this.l = this.l.getNext();
    return ret;
      }
   }

    bool hasNext() {
      return TDoubleLinkedList.got(this.l);
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         TDoubleLinkedList.access$000(this.this$0, this.current);
         this.current = nullptr;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
