#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/map/hash/TCharLongHashMap/TCharLongValueHashIterator.h"
#include "gnu/trove/map/hash/TCharLongHashMap/TValueView/1.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharLongHashMap {
public:
   protected TCharLongHashMap$TValueView(TCharLongHashMap var1) {
      this.this$0 = var1;
   }

    TLongIterator iterator() {
      return std::make_shared<TCharLongValueHashIterator>(this.this$0, this.this$0);
   }

    long getNoEntryValue() {
      return TCharLongHashMap.access$400(this.this$0);
   }

    int size() {
      return TCharLongHashMap.access$500(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TCharLongHashMap.access$600(this.this$0);
   }

    bool contains(long entry) {
      return this.this$0.containsValue(entry);
   }

   public long[] toArray() {
      return this.this$0.values();
   }

   public long[] toArray(long[] dest) {
      return this.this$0.values(dest);
   }

    bool add(long entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(long entry) {
      long[] values = this.this$0._values;
      char[] set = this.this$0._set;
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
    for (auto& element : collection)         if (!(dynamic_cast<int64_t*>(element) != nullptr)) {
    return false;
         }

    long ele = (int64_t)element;
         if (!this.this$0.containsValue(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TLongCollection collection) {
    TLongIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsValue(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(long[] array) {
    for (auto& element : array)         if (!this.this$0.containsValue(element)) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(TLongCollection collection) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(long[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TLongIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TLongCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TLongIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(long[] array) {
    bool changed = false;
      Arrays.sort(array);
      long[] values = this.this$0._values;
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

    for (auto& element : collection)         if (dynamic_cast<int64_t*>(element) != nullptr) {
    long c = (int64_t)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TLongCollection collection) {
      if (this == collection) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TLongIterator iter = collection.iterator();

         while (iter.hasNext()) {
    long element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(long[] array) {
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

    bool forEach(TLongProcedure procedure) {
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
