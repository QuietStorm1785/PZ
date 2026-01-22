#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/map/custom_hash/TObjectByteCustomHashMap/TByteValueCollection/1.h"
#include "gnu/trove/map/custom_hash/TObjectByteCustomHashMap/TByteValueCollection/TObjectByteValueHashIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectByteCustomHashMap {
public:
   TObjectByteCustomHashMap$TByteValueCollection(TObjectByteCustomHashMap var1) {
      this.this$0 = var1;
   }

    TByteIterator iterator() {
      return std::make_shared<TObjectByteValueHashIterator>(this);
   }

    uint8_t getNoEntryValue() {
      return this.this$0.no_entry_value;
   }

    int size() {
      return TObjectByteCustomHashMap.access$100(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TObjectByteCustomHashMap.access$200(this.this$0);
   }

    bool contains(uint8_t entry) {
      return this.this$0.containsValue(entry);
   }

   public byte[] toArray() {
      return this.this$0.values();
   }

   public byte[] toArray(byte[] dest) {
      return this.this$0.values(dest);
   }

    bool add(uint8_t entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(uint8_t entry) {
      byte[] values = this.this$0._values;
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
    for (auto& element : collection)         if (!(dynamic_cast<uint8_t*>(element) != nullptr)) {
    return false;
         }

    uint8_t ele = (uint8_t)element;
         if (!this.this$0.containsValue(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TByteCollection collection) {
    TByteIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsValue(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(byte[] array) {
    for (auto& element : array)         if (!this.this$0.containsValue(element)) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(TByteCollection collection) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool addAll(byte[] array) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainAll(Collection<?> collection) {
    bool modified = false;
    TByteIterator iter = this.iterator();

      while (iter.hasNext()) {
         if (!collection.contains(iter.next())) {
            iter.remove();
            modified = true;
         }
      }

    return modified;
   }

    bool retainAll(TByteCollection collection) {
      if (this == collection) {
    return false;
      } else {
    bool modified = false;
    TByteIterator iter = this.iterator();

         while (iter.hasNext()) {
            if (!collection.contains(iter.next())) {
               iter.remove();
               modified = true;
            }
         }

    return modified;
      }
   }

    bool retainAll(byte[] array) {
    bool changed = false;
      Arrays.sort(array);
      byte[] values = this.this$0._values;
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

    for (auto& element : collection)         if (dynamic_cast<uint8_t*>(element) != nullptr) {
    uint8_t c = (uint8_t)element;
            if (this.remove(c)) {
               changed = true;
            }
         }
      }

    return changed;
   }

    bool removeAll(TByteCollection collection) {
      if (this == collection) {
         this.clear();
    return true;
      } else {
    bool changed = false;
    TByteIterator iter = collection.iterator();

         while (iter.hasNext()) {
    uint8_t element = iter.next();
            if (this.remove(element)) {
               changed = true;
            }
         }

    return changed;
      }
   }

    bool removeAll(byte[] array) {
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

    bool forEach(TByteProcedure procedure) {
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
