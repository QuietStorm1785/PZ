#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/util/Exceptions.h"

namespace zombie {
namespace util {
namespace list {


class AbstractIntList {
public:
    int ptr;
    int lptr;

   AbstractIntList$1(AbstractIntList var1, int var2) {
      this.this$0 = var1;
      this.val$index = var2;
      this.ptr = this.val$index;
      this.lptr = -1;
   }

    bool hasNext() {
      return this.ptr < this.this$0.size();
   }

    int next() {
      if (this.ptr == this.this$0.size()) {
         Exceptions.endOfIterator();
      }

      this.lptr = this.ptr++;
      return this.this$0.get(this.lptr);
   }

    void remove() {
      if (this.lptr == -1) {
         Exceptions.noElementToRemove();
      }

      this.this$0.removeElementAt(this.lptr);
      if (this.lptr < this.ptr) {
         this.ptr--;
      }

      this.lptr = -1;
   }

    void add(int var1) {
      this.this$0.push_back(this.ptr++, var1);
      this.lptr = -1;
   }

    bool hasPrevious() {
      return this.ptr > 0;
   }

    int nextIndex() {
      return this.ptr;
   }

    int previous() {
      if (this.ptr == 0) {
         Exceptions.startOfIterator();
      }

      this.ptr--;
      this.lptr = this.ptr;
      return this.this$0.get(this.ptr);
   }

    int previousIndex() {
      return this.ptr - 1;
   }

    void set(int var1) {
      if (this.lptr == -1) {
         Exceptions.noElementToSet();
      }

      this.this$0.set(this.lptr, var1);
   }
}
} // namespace list
} // namespace util
} // namespace zombie
