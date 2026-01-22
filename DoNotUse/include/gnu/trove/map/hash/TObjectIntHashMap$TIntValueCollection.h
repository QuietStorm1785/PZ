#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/map/hash/TObjectIntHashMap/TIntValueCollection/1.h"
#include "gnu/trove/map/hash/TObjectIntHashMap/TIntValueCollection/TObjectIntValueHashIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectIntHashMap {
public:
   TObjectIntHashMap$TIntValueCollection(TObjectIntHashMap var1) {
      this.this$0 = var1;
   }

    TIntIterator iterator() {
      return std::make_shared<TObjectIntValueHashIterator>(this);
   }

    int getNoEntryValue() {
      return this.this$0.no_entry_value;
   }

    int size() {
      return TObjectIntHashMap.access$100(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TObjectIntHashMap.access$200(this.this$0);
   }

    bool contains(int entry) {
      return this.this$0.containsValue(entry);
   }

   public int[] toArray() {
      return this.this$0.values();
   }

   public int[] toArray(int[] dest) {
      return this.this$0.values(dest);
   }

    bool add(int entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(int entry) {
      int[] values = this.this$0._values;
      Object[] set = this.this$0._set;
    int i = values.length;

      while (i-- > 0) {
         if (set[i] != TObjectHash.FREE && set[i] != TObjectHash.REMOVED && entry == values[i]) {
            this.this$0.removeAt(i);
    return true;
         }
      }

    return false;
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<int*>(element) != nullptr)) {
    return false;
         }

    int ele = (int)element;
         if (!this.this$0.containsValue(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TIntCollection collection) {
    TIntIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsValue(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(int[] array) {
    for (auto& element : array)         if (!this.this$0.containsValue(element)) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(TIntCollection collection) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(int[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TIntIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TIntCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TIntIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(int[] array) {
    bool changed = false;
      Arrays.sort(array);
      int[] values = this.this$0._values;
      Object[] set = this.this$0._set;
    int i = set.length;

      while (i-- > 0) {
         if (set[i] != TObjectHash.FREE && set[i] != TObjectHash.REMOVED && Arrays.binarySearch(array, values[i]) < 0) {
            this.this$0.removeAt(i);
            changed = true;
         }
      }

    return changed;
   }

    bool removeAll(Collection<?> collection) {
    bool changed = false;

    for (auto& element : collection)         if (dynamic_cast<int*>(element) != nullptr) {
    int c = (int)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TIntCollection collection) {
      if (this == collection) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TIntIterator iter = collection.iterator();

         while (iter.hasNext()) {
    int element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(int[] array) {
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

    bool forEach(TIntProcedure procedure) {
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
