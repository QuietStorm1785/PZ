#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/map/hash/TLongCharHashMap/TKeyView/1.h"
#include "gnu/trove/map/hash/TLongCharHashMap/TLongCharKeyHashIterator.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TLongCharHashMap {
public:
   protected TLongCharHashMap$TKeyView(TLongCharHashMap var1) {
      this.this$0 = var1;
   }

    TLongIterator iterator() {
      return std::make_shared<TLongCharKeyHashIterator>(this.this$0, this.this$0);
   }

    long getNoEntryValue() {
      return TLongCharHashMap.access$000(this.this$0);
   }

    int size() {
      return TLongCharHashMap.access$100(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TLongCharHashMap.access$200(this.this$0);
   }

    bool contains(long entry) {
      return this.this$0.contains(entry);
   }

   public long[] toArray() {
      return this.this$0.keys();
   }

   public long[] toArray(long[] dest) {
      return this.this$0.keys(dest);
   }

    bool add(long entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(long entry) {
      return TLongCharHashMap.access$300(this.this$0) != this.this$0.remove(entry);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<int64_t*>(element) != nullptr)) {
    return false;
         }

    long ele = (int64_t)element;
         if (!this.this$0.containsKey(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TLongCollection collection) {
    TLongIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsKey(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(long[] array) {
    for (auto& element : array)         if (!this.this$0.contains(element)) {
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
      long[] set = this.this$0._set;
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
      return this.this$0.forEachKey(procedure);
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TLongSet*>(other) != nullptr)) {
    return false;
      } else {
    TLongSet that = (TLongSet)other;
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
