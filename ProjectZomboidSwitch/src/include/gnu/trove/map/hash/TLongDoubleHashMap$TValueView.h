#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/map/hash/TLongDoubleHashMap/TLongDoubleValueHashIterator.h"
#include "gnu/trove/map/hash/TLongDoubleHashMap/TValueView/1.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TLongDoubleHashMap {
public:
   protected TLongDoubleHashMap$TValueView(TLongDoubleHashMap var1) {
      this.this$0 = var1;
   }

    TDoubleIterator iterator() {
      return std::make_shared<TLongDoubleValueHashIterator>(this.this$0, this.this$0);
   }

    double getNoEntryValue() {
      return TLongDoubleHashMap.access$400(this.this$0);
   }

    int size() {
      return TLongDoubleHashMap.access$500(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TLongDoubleHashMap.access$600(this.this$0);
   }

    bool contains(double entry) {
      return this.this$0.containsValue(entry);
   }

   public double[] toArray() {
      return this.this$0.values();
   }

   public double[] toArray(double[] dest) {
      return this.this$0.values(dest);
   }

    bool add(double entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(double entry) {
      double[] values = this.this$0._values;
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
    for (auto& element : collection)         if (!(dynamic_cast<double*>(element) != nullptr)) {
    return false;
         }

    double ele = (double)element;
         if (!this.this$0.containsValue(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TDoubleCollection collection) {
    TDoubleIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsValue(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(double[] array) {
    for (auto& element : array)         if (!this.this$0.containsValue(element)) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(TDoubleCollection collection) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(double[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TDoubleIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TDoubleCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TDoubleIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(double[] array) {
    bool changed = false;
      Arrays.sort(array);
      double[] values = this.this$0._values;
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

    for (auto& element : collection)         if (dynamic_cast<double*>(element) != nullptr) {
    double c = (double)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TDoubleCollection collection) {
      if (this == collection) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TDoubleIterator iter = collection.iterator();

         while (iter.hasNext()) {
    double element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(double[] array) {
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

    bool forEach(TDoubleProcedure procedure) {
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
