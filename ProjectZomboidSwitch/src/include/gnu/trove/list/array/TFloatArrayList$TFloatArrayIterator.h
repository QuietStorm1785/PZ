#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/iterator/TFloatIterator.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace array {


class TFloatArrayList {
public:
    int cursor;
    int lastRet;

   TFloatArrayList$TFloatArrayIterator(TFloatArrayList var1, int index) {
      this.this$0 = var1;
      this.cursor = 0;
      this.lastRet = -1;
      this.cursor = index;
   }

    bool hasNext() {
      return this.cursor < this.this$0.size();
   }

    float next() {
      try {
    float next = this.this$0.get(this.cursor);
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
