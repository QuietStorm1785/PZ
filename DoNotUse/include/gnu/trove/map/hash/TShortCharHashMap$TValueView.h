#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/iterator/TCharIterator.h"
#include "gnu/trove/map/hash/TShortCharHashMap/TShortCharValueHashIterator.h"
#include "gnu/trove/map/hash/TShortCharHashMap/TValueView/1.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TShortCharHashMap {
public:
   protected TShortCharHashMap$TValueView(TShortCharHashMap var1) {
      this.this$0 = var1;
   }

    TCharIterator iterator() {
      return std::make_shared<TShortCharValueHashIterator>(this.this$0, this.this$0);
   }

    char getNoEntryValue() {
      return TShortCharHashMap.access$400(this.this$0);
   }

    int size() {
      return TShortCharHashMap.access$500(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TShortCharHashMap.access$600(this.this$0);
   }

    bool contains(char entry) {
      return this.this$0.containsValue(entry);
   }

   public char[] toArray() {
      return this.this$0.values();
   }

   public char[] toArray(char[] dest) {
      return this.this$0.values(dest);
   }

    bool add(char entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(char entry) {
      char[] values = this.this$0._values;
      short[] set = this.this$0._set;
    int i = values.length;

      while (i-- > 0) {
         if (set[i] != 0 && set[i] != 2 && entry == values[i]) {
            this.this$0.removeAt(i);
    return true;
         }
      }

    return false;
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<char*>(element) != nullptr)) {
    return false;
         }

    char ele = (char)element;
         if (!this.this$0.containsValue(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TCharCollection collection) {
    TCharIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsValue(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(char[] array) {
    for (auto& element : array)         if (!this.this$0.containsValue(element)) {
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
      char[] values = this.this$0._values;
      byte[] states = this.this$0._states;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1 && Arrays.binarySearch(array, values[i]) < 0) {
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
      return this.this$0.forEachValue(procedure);
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.this$0.forEachValue(std::make_shared<1>(this, buf));
      buf.append("}");
      return buf;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
