#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/TFloatIterator.h"
#include "gnu/trove/map/custom_hash/TObjectFloatCustomHashMap/TFloatValueCollection/1.h"
#include "gnu/trove/map/custom_hash/TObjectFloatCustomHashMap/TFloatValueCollection/TObjectFloatValueHashIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectFloatCustomHashMap {
public:
   TObjectFloatCustomHashMap$TFloatValueCollection(TObjectFloatCustomHashMap var1) {
      this.this$0 = var1;
   }

    TFloatIterator iterator() {
      return std::make_shared<TObjectFloatValueHashIterator>(this);
   }

    float getNoEntryValue() {
      return this.this$0.no_entry_value;
   }

    int size() {
      return TObjectFloatCustomHashMap.access$100(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TObjectFloatCustomHashMap.access$200(this.this$0);
   }

    bool contains(float entry) {
      return this.this$0.containsValue(entry);
   }

   public float[] toArray() {
      return this.this$0.values();
   }

   public float[] toArray(float[] dest) {
      return this.this$0.values(dest);
   }

    bool add(float entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(float entry) {
      float[] values = this.this$0._values;
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
    for (auto& element : collection)         if (!(dynamic_cast<float*>(element) != nullptr)) {
    return false;
         }

    float ele = (float)element;
         if (!this.this$0.containsValue(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TFloatCollection collection) {
    TFloatIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsValue(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(float[] array) {
    for (auto& element : array)         if (!this.this$0.containsValue(element)) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(TFloatCollection collection) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(float[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TFloatIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TFloatCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TFloatIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(float[] array) {
    bool changed = false;
      Arrays.sort(array);
      float[] values = this.this$0._values;
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

    for (auto& element : collection)         if (dynamic_cast<float*>(element) != nullptr) {
    float c = (float)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TFloatCollection collection) {
      if (this == collection) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TFloatIterator iter = collection.iterator();

         while (iter.hasNext()) {
    float element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(float[] array) {
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

    bool forEach(TFloatProcedure procedure) {
      return this.this$0.forEachValue(procedure);
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.this$0.forEachValue(std::make_shared<1>(this, buf));
      buf.append("}");
      return buf;
   }
}
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
