#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IntIterator.h"
#include "zombie/util/util/Exceptions.h"

namespace zombie {
namespace util {
namespace set {


class IntOpenHashSet {
public:
    int nextEntry;
    int lastEntry;

   IntOpenHashSet$1(IntOpenHashSet var1) {
      this.this$0 = var1;
      this.nextEntry = this.nextEntry(0);
      this.lastEntry = -1;
   }

    int nextEntry(int var1) {
      while (var1 < this.this$0.data.length && this.this$0.states[var1] != 1) {
         var1++;
      }

    return var1;
   }

    bool hasNext() {
      return this.nextEntry < this.this$0.data.length;
   }

    int next() {
      if (!this.hasNext()) {
         Exceptions.endOfIterator();
      }

      this.lastEntry = this.nextEntry;
      this.nextEntry = this.nextEntry(this.nextEntry + 1);
      return this.this$0.data[this.lastEntry];
   }

    void remove() {
      if (this.lastEntry == -1) {
         Exceptions.noElementToRemove();
      }

      this.this$0.states[this.lastEntry] = 2;
      this.this$0.size--;
      this.lastEntry = -1;
   }
}
} // namespace set
} // namespace util
} // namespace zombie
