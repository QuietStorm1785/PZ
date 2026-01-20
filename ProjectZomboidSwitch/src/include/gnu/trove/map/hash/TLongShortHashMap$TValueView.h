#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/iterator/TShortIterator.h"
#include "gnu/trove/map/hash/TLongShortHashMap/TLongShortValueHashIterator.h"
#include "gnu/trove/map/hash/TLongShortHashMap/TValueView/1.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TLongShortHashMap {
public:
   protected TLongShortHashMap$TValueView(TLongShortHashMap var1) {
      this.this$0 = var1;
   }

    TShortIterator iterator() {
      return std::make_shared<TLongShortValueHashIterator>(this.this$0, this.this$0);
   }

    short getNoEntryValue() {
      return TLongShortHashMap.access$400(this.this$0);
   }

    int size() {
      return TLongShortHashMap.access$500(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TLongShortHashMap.access$600(this.this$0);
   }

    bool contains(short entry) {
      return this.this$0.containsValue(entry);
   }

   public short[] toArray() {
      return this.this$0.values();
   }

   public short[] toArray(short[] dest) {
      return this.this$0.values(dest);
   }

    bool add(short entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(short entry) {
      short[] values = this.this$0._values;
      long[] set = this.this$0._set;
    int i = values.length;

      while (i-- > 0) {
         if (set[i] != 0L && set[i] != 2L && entry == values[i]) {
            this.this$0.removeAt(i);
    return true;
         }
      }

    return false;
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<int16_t*>(element) != nullptr)) {
    return false;
         }

    short ele = (int16_t)element;
         if (!this.this$0.containsValue(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TShortCollection collection) {
    TShortIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsValue(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(short[] array) {
    for (auto& element : array)         if (!this.this$0.containsValue(element)) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(TShortCollection collection) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(short[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TShortIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TShortCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TShortIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(short[] array) {
    bool changed = false;
      Arrays.sort(array);
      short[] values = this.this$0._values;
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

    for (auto& element : collection)         if (dynamic_cast<int16_t*>(element) != nullptr) {
    short c = (int16_t)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TShortCollection collection) {
      if (this == collection) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TShortIterator iter = collection.iterator();

         while (iter.hasNext()) {
    short element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(short[] array) {
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

    bool forEach(TShortProcedure procedure) {
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
