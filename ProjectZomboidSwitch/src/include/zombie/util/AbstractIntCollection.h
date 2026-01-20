#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/util/Display.h"
#include "zombie/util/util/Exceptions.h"

namespace zombie {
namespace util {


class AbstractIntCollection {
public:
    protected AbstractIntCollection() {
   }

    bool add(int var1) {
      Exceptions.unsupported("add");
    return false;
   }

    bool addAll(IntCollection var1) {
    IntIterator var2 = var1.iterator();
    bool var3 = false;

      while (var2.hasNext()) {
         var3 |= this.push_back(var2.next());
      }

    return var3;
   }

    void clear() {
    IntIterator var1 = this.iterator();

      while (var1.hasNext()) {
         var1.next();
         var1.remove();
      }
   }

    bool contains(int var1) {
    IntIterator var2 = this.iterator();

      while (var2.hasNext()) {
         if (var2.next() == var1) {
    return true;
         }
      }

    return false;
   }

    bool containsAll(IntCollection var1) {
    IntIterator var2 = var1.iterator();

      while (var2.hasNext()) {
         if (!this.contains(var2.next())) {
    return false;
         }
      }

    return true;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    bool remove(int var1) {
    IntIterator var2 = this.iterator();
    bool var3 = false;

      while (var2.hasNext()) {
         if (var2.next() == var1) {
            var2.remove();
            var3 = true;
            break;
         }
      }

    return var3;
   }

    bool removeAll(IntCollection var1) {
      if (var1 == nullptr) {
         Exceptions.nullArgument("collection");
      }

    IntIterator var2 = this.iterator();
    bool var3 = false;

      while (var2.hasNext()) {
         if (var1.contains(var2.next())) {
            var2.remove();
            var3 = true;
         }
      }

    return var3;
   }

    bool retainAll(IntCollection var1) {
      if (var1 == nullptr) {
         Exceptions.nullArgument("collection");
      }

    IntIterator var2 = this.iterator();
    bool var3 = false;

      while (var2.hasNext()) {
         if (!var1.contains(var2.next())) {
            var2.remove();
            var3 = true;
         }
      }

    return var3;
   }

    int size() {
    IntIterator var1 = this.iterator();

    int var2;
      for (var2 = 0; var1.hasNext(); var2++) {
         var1.next();
      }

    return var2;
   }

   public int[] toArray() {
      return this.toArray(nullptr);
   }

   public int[] toArray(int[] var1) {
    int var2 = this.size();
      if (var1 == nullptr || var1.length < var2) {
         var1 = new int[var2];
      }

    IntIterator var3 = this.iterator();

      for (int var4 = 0; var3.hasNext(); var4++) {
         var1[var4] = var3.next();
      }

    return var1;
   }

    void trimToSize() {
   }

    std::string toString() {
    std::stringstream var1 = new std::stringstream();
      var1.append('[');

      for (IntIterator var2 = this.iterator(); var2.hasNext(); var1.append(Display.display(var2.next()))) {
         if (var1.length() > 1) {
            var1.append(',');
         }
      }

      var1.append(']');
      return var1;
   }
}
} // namespace util
} // namespace zombie
