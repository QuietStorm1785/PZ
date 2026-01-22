#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/hash/DefaultIntHashFunction.h"

namespace zombie {
namespace util {
namespace map {


class AbstractIntKeyMap {
public:
    protected AbstractIntKeyMap() {
   }

    void clear() {
    IntKeyMapIterator var1 = this.entries();

      while (var1.hasNext()) {
         var1.next();
         var1.remove();
      }
   }

    V remove(int var1) {
    IntKeyMapIterator var2 = this.entries();

      while (var2.hasNext()) {
         var2.next();
         if (var2.getKey() == var1) {
    void* var3 = var2.getValue();
            var2.remove();
            return (V)var3;
         }
      }

    return nullptr;
   }

    void putAll(IntKeyMap<V> var1) {
    IntKeyMapIterator var2 = var1.entries();

      while (var2.hasNext()) {
         var2.next();
         this.put(var2.getKey(), var2.getValue());
      }
   }

    bool containsKey(int var1) {
    IntKeyMapIterator var2 = this.entries();

      while (var2.hasNext()) {
         var2.next();
         if (var2.getKey() == var1) {
    return true;
         }
      }

    return false;
   }

    V get(int var1) {
    IntKeyMapIterator var2 = this.entries();

      while (var2.hasNext()) {
         var2.next();
         if (var2.getKey() == var1) {
            return (V)var2.getValue();
         }
      }

    return nullptr;
   }

    bool containsValue(void* var1) {
    IntKeyMapIterator var2 = this.entries();
      if (var1 == nullptr) {
         while (var2.hasNext()) {
            var2.next();
            if (var1 == nullptr) {
    return true;
            }
         }
      } else {
         while (var2.hasNext()) {
            var2.next();
            if (var1 == var2.getValue())) {
    return true;
            }
         }
      }

    return false;
   }

    bool equals(void* var1) {
      if (!(dynamic_cast<IntKeyMap*>(var1) != nullptr var2)) {
    return false;
      } else if (this.size() != var2.size()) {
    return false;
      } else {
    IntKeyMapIterator var3 = this.entries();

         while (var3.hasNext()) {
            var3.next();
    int var4 = var3.getKey();
    void* var5 = var3.getValue();
            if (var5 == nullptr) {
               if (var2.get(var4) != nullptr) {
    return false;
               }

               if (!var2.containsKey(var4)) {
    return false;
               }
            } else if (!var5 == var2.get(var4))) {
    return false;
            }
         }

    return true;
      }
   }

    int hashCode() {
    int var1 = 0;

      for (IntKeyMapIterator var2 = this.entries(); var2.hasNext(); var1 += DefaultIntHashFunction.INSTANCE.hash(var2.getKey()) ^ var2.getValue().hashCode()) {
         var2.next();
      }

    return var1;
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    int size() {
    int var1 = 0;

      for (IntKeyMapIterator var2 = this.entries(); var2.hasNext(); var1++) {
         var2.next();
      }

    return var1;
   }

    std::string toString() {
    std::stringstream var1 = new std::stringstream();
      var1.append('[');
    IntKeyMapIterator var2 = this.entries();

      while (var2.hasNext()) {
         if (var1.length() > 1) {
            var1.append(',');
         }

         var2.next();
         var1.append(std::string.valueOf(var2.getKey()));
         var1.append("->");
         var1.append(std::string.valueOf(var2.getValue()));
      }

      var1.append(']');
      return var1;
   }

    void trimToSize() {
   }
}
} // namespace map
} // namespace util
} // namespace zombie
