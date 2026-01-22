#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/map/hash/TByteObjectHashMap/KeyView/TByteHashIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TByteObjectHashMap {
public:
   TByteObjectHashMap$KeyView(TByteObjectHashMap var1) {
      this.this$0 = var1;
   }

    uint8_t getNoEntryValue() {
      return this.this$0.no_entry_key;
   }

    int size() {
      return TByteObjectHashMap.access$000(this.this$0);
   }

    bool isEmpty() {
      return TByteObjectHashMap.access$100(this.this$0) == 0;
   }

    bool contains(uint8_t entry) {
      return this.this$0.containsKey(entry);
   }

    TByteIterator iterator() {
      return std::make_shared<TByteHashIterator>(this, this.this$0);
   }

   public byte[] toArray() {
      return this.this$0.keys();
   }

   public byte[] toArray(byte[] dest) {
      return this.this$0.keys(dest);
   }

    bool add(uint8_t entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(uint8_t entry) {
      return nullptr != this.this$0.remove(entry);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!this.this$0.containsKey((uint8_t)element)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TByteCollection collection) {
      if (collection == this) {
    return true;
      } else {
    TByteIterator iter = collection.iterator();

         while (iter.hasNext()) {
            if (!this.this$0.containsKey(iter.next())) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(byte[] array) {
    for (auto& element : array)         if (!this.this$0.containsKey(element)) {
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
      byte[] set = this.this$0._set;
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
      if (collection == this) {
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
      return this.this$0.forEachKey(procedure);
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TByteSet*>(other) != nullptr)) {
    return false;
      } else {
    TByteSet that = (TByteSet)other;
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
    bool first = true;
    int i = this.this$0._states.length;

      while (i-- > 0) {
         if (this.this$0._states[i] == 1) {
            if (first) {
               first = false;
            } else {
               buf.append(",");
            }

            buf.append(this.this$0._set[i]);
         }
      }

      return buf;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
