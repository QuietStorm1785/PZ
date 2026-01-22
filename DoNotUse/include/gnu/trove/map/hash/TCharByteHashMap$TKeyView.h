#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TCharIterator.h"
#include "gnu/trove/map/hash/TCharByteHashMap/TCharByteKeyHashIterator.h"
#include "gnu/trove/map/hash/TCharByteHashMap/TKeyView/1.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/set/TCharSet.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharByteHashMap {
public:
   protected TCharByteHashMap$TKeyView(TCharByteHashMap var1) {
      this.this$0 = var1;
   }

    TCharIterator iterator() {
      return std::make_shared<TCharByteKeyHashIterator>(this.this$0, this.this$0);
   }

    char getNoEntryValue() {
      return TCharByteHashMap.access$000(this.this$0);
   }

    int size() {
      return TCharByteHashMap.access$100(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TCharByteHashMap.access$200(this.this$0);
   }

    bool contains(char entry) {
      return this.this$0.contains(entry);
   }

   public char[] toArray() {
      return this.this$0.keys();
   }

   public char[] toArray(char[] dest) {
      return this.this$0.keys(dest);
   }

    bool add(char entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(char entry) {
      return TCharByteHashMap.access$300(this.this$0) != this.this$0.remove(entry);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<char*>(element) != nullptr)) {
    return false;
         }

    char ele = (char)element;
         if (!this.this$0.containsKey(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TCharCollection collection) {
    TCharIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsKey(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(char[] array) {
    for (auto& element : array)         if (!this.this$0.contains(element)) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(TCharCollection collection) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(char[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TCharIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TCharCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TCharIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(char[] array) {
    bool changed = false;
      Arrays.sort(array);
      char[] set = this.this$0._set;
      byte[] states = this.this$0._states;
    int i = set.length;

      while (i-- > 0) {
         if (states[i] == 1 && Arrays.binarySearch(array, set[i]) < 0) {
            this.this$0.removeAt(i);
            changed = true;
         }
      }

    return changed;
   }

    bool removeAll(Collection<?> collection) {
    bool changed = false;

    for (auto& element : collection)         if (dynamic_cast<char*>(element) != nullptr) {
    char c = (char)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TCharCollection collection) {
      if (this == collection) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TCharIterator iter = collection.iterator();

         while (iter.hasNext()) {
    char element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(char[] array) {
    bool changed = false;
    int i = array.length;

      while (i-- > 0) {
         if (this.remove(array[i])) {
            changed = true;
         }
      }

    return changed;
   }

    void clear() {
      this.this$0.clear();
   }

    bool forEach(TCharProcedure procedure) {
      return this.this$0.forEachKey(procedure);
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TCharSet*>(other) != nullptr)) {
    return false;
      } else {
    TCharSet that = (TCharSet)other;
         if (that.size() != this.size()) {
    return false;
         } else {
    int i = this.this$0._states.length;

            while (i-- > 0) {
               if (this.this$0._states[i] == 1 && !that.contains(this.this$0._set[i])) {
    return false;
               }
            }

    return true;
         }
      }
   }

    int hashCode() {
    int hashcode = 0;
    int i = this.this$0._states.length;

      while (i-- > 0) {
         if (this.this$0._states[i] == 1) {
            hashcode += HashFunctions.hash(this.this$0._set[i]);
         }
      }

    return hashcode;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.this$0.forEachKey(std::make_shared<1>(this, buf));
      buf.append("}");
      return buf;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
