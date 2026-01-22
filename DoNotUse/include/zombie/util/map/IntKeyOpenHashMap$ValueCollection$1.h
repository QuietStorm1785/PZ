#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/map/IntKeyOpenHashMap/ValueCollection.h"
#include "zombie/util/util/Exceptions.h"
#include <iterator>

namespace zombie {
namespace util {
namespace map {


class IntKeyOpenHashMap {
public:
    int nextEntry;
    int lastEntry;

   IntKeyOpenHashMap$ValueCollection$1(ValueCollection var1) {
      this.this$1 = var1;
      this.nextEntry = this.nextEntry(0);
      this.lastEntry = -1;
   }

    int nextEntry(int var1) {
      while (var1 < this.this$1.this$0.keys.length && this.this$1.this$0.states[var1] != 1) {
         var1++;
      }

    return var1;
   }

    bool hasNext() {
      return this.nextEntry < this.this$1.this$0.keys.length;
   }

    V next() {
      if (!this.hasNext()) {
         Exceptions.endOfIterator();
      }

      this.lastEntry = this.nextEntry;
      this.nextEntry = this.nextEntry(this.nextEntry + 1);
      return (V)this.this$1.this$0.values[this.lastEntry];
   }

    void remove() {
      if (this.lastEntry == -1) {
         Exceptions.noElementToRemove();
      }

      this.this$1.this$0.states[this.lastEntry] = 2;
      this.this$1.this$0.values[this.lastEntry] = nullptr;
      this.this$1.this$0.size--;
      this.lastEntry = -1;
   }
}
} // namespace map
} // namespace util
} // namespace zombie
