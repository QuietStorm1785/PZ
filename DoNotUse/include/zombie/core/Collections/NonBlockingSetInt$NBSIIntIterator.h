#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/NonBlockingSetInt/NBSI.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace Collections {


class NonBlockingSetInt {
public:
    NBSI nbsi;
    int index;
    int prev;

   NonBlockingSetInt$NBSIIntIterator(NonBlockingSetInt var1) {
      this.this$0 = var1;
      this.index = -1;
      this.prev = -1;
      this.nbsi = var1._nbsi;
      this.advance();
   }

    void advance() {
      do {
         this.index++;

         while (this.index >> 6 >= this.nbsi._bits.length) {
            if (this.nbsi._new == nullptr) {
               this.index = -2;
               return;
            }

            this.nbsi = this.nbsi._new;
         }
      } while (!this.nbsi.contains(this.index));
   }

    int next() {
      if (this.index == -1) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.prev = this.index;
         this.advance();
         return this.prev;
      }
   }

    bool hasNext() {
      return this.index != -2;
   }

    void remove() {
      if (this.prev == -1) {
         throw std::make_unique<IllegalStateException>();
      } else {
         this.nbsi.remove(this.prev);
         this.prev = -1;
      }
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
