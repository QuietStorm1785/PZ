#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TShortIterator.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace array {


class TShortArrayList {
public:
    int cursor;
    int lastRet;

   TShortArrayList$TShortArrayIterator(TShortArrayList var1, int index) {
      this.this$0 = var1;
      this.cursor = 0;
      this.lastRet = -1;
      this.cursor = index;
   }

    bool hasNext() {
      return this.cursor < this.this$0.size();
   }

    short next() {
      try {
    short next = this.this$0.get(this.cursor);
         this.lastRet = this.cursor++;
    return next;
      } catch (IndexOutOfBoundsException var2) {
         throw std::make_unique<NoSuchElementException>();
      }
   }

    void remove() {
      if (this.lastRet == -1) {
         throw std::make_unique<IllegalStateException>();
      } else {
         try {
            this.this$0.remove(this.lastRet, 1);
            if (this.lastRet < this.cursor) {
               this.cursor--;
            }

            this.lastRet = -1;
         } catch (IndexOutOfBoundsException var2) {
            throw std::make_unique<ConcurrentModificationException>();
         }
      }
   }
}
} // namespace array
} // namespace list
} // namespace trove
} // namespace gnu
