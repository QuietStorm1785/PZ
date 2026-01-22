#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/AbstractIntCollection.h"
#include "zombie/util/IntCollection.h"
#include "zombie/util/IntIterator.h"
#include "zombie/util/hash/DefaultIntHashFunction.h"
#include "zombie/util/list/AbstractIntList/1.h"
#include "zombie/util/util/Exceptions.h"

namespace zombie {
namespace util {
namespace list {


class AbstractIntList : public AbstractIntCollection {
public:
    protected AbstractIntList() {
   }

    bool add(int var1) {
      this.push_back(this.size(), var1);
    return true;
   }

    void add(int var1, int var2) {
      Exceptions.unsupported("add");
   }

    bool addAll(int var1, IntCollection var2) {
      if (var1 < 0 || var1 > this.size()) {
         Exceptions.indexOutOfBounds(var1, 0, this.size());
      }

    IntIterator var3 = var2.iterator();

    bool var4;
      for (var4 = var3.hasNext(); var3.hasNext(); var1++) {
         this.push_back(var1, var3.next());
      }

    return var4;
   }

    int indexOf(int var1) {
      return this.indexOf(0, var1);
   }

    int indexOf(int var1, int var2) {
    IntListIterator var3 = this.listIterator(var1);

      while (var3.hasNext()) {
         if (var3.next() == var2) {
            return var3.previousIndex();
         }
      }

      return -1;
   }

    IntIterator iterator() {
      return this.listIterator();
   }

    int lastIndexOf(int var1) {
    IntListIterator var2 = this.listIterator(this.size());

      while (var2.hasPrevious()) {
         if (var2.previous() == var1) {
            return var2.nextIndex();
         }
      }

      return -1;
   }

    int lastIndexOf(int var1, int var2) {
    IntListIterator var3 = this.listIterator(var1);

      while (var3.hasPrevious()) {
         if (var3.previous() == var2) {
            return var3.nextIndex();
         }
      }

      return -1;
   }

    IntListIterator listIterator() {
      return this.listIterator(0);
   }

    IntListIterator listIterator(int var1) {
      if (var1 < 0 || var1 > this.size()) {
         Exceptions.indexOutOfBounds(var1, 0, this.size());
      }

      return std::make_shared<1>(this, var1);
   }

    int removeElementAt(int var1) {
      Exceptions.unsupported("removeElementAt");
      throw std::make_unique<RuntimeException>();
   }

    bool equals(void* var1) {
      if (this == var1) {
    return true;
      } else if (!(dynamic_cast<IntList*>(var1) != nullptr)) {
    return false;
      } else {
    IntListIterator var2 = this.listIterator();
    IntListIterator var3 = ((IntList)var1).listIterator();

         while (var2.hasNext() && var3.hasNext()) {
            if (var2.next() != var3.next()) {
    return false;
            }
         }

         return !var2.hasNext() && !var3.hasNext();
      }
   }

    int hashCode() {
    int var1 = 1;
    IntIterator var2 = this.iterator();

      while (var2.hasNext()) {
         var1 = 31 * var1 + DefaultIntHashFunction.INSTANCE.hash(var2.next());
      }

    return var1;
   }
}
} // namespace list
} // namespace util
} // namespace zombie
