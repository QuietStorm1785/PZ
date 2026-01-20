#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TIntIterator.h"
#include "gnu/trove/map/hash/TIntShortHashMap/TIntShortKeyHashIterator.h"
#include "gnu/trove/map/hash/TIntShortHashMap/TKeyView/1.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TIntShortHashMap {
public:
   protected TIntShortHashMap$TKeyView(TIntShortHashMap var1) {
      this.this$0 = var1;
   }

    TIntIterator iterator() {
      return std::make_shared<TIntShortKeyHashIterator>(this.this$0, this.this$0);
   }

    int getNoEntryValue() {
      return TIntShortHashMap.access$000(this.this$0);
   }

    int size() {
      return TIntShortHashMap.access$100(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TIntShortHashMap.access$200(this.this$0);
   }

    bool contains(int entry) {
      return this.this$0.contains(entry);
   }

   public int[] toArray() {
      return this.this$0.keys();
   }

   public int[] toArray(int[] dest) {
      return this.this$0.keys(dest);
   }

    bool add(int entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(int entry) {
      return TIntShortHashMap.access$300(this.this$0) != this.this$0.remove(entry);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<int*>(element) != nullptr)) {
    return false;
         }

    int ele = (int)element;
         if (!this.this$0.containsKey(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TIntCollection collection) {
    TIntIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsKey(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(int[] array) {
    for (auto& element : array)         if (!this.this$0.contains(element)) {
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
      int[] set = this.this$0._set;
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
      return this.this$0.forEachKey(procedure);
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TIntSet*>(other) != nullptr)) {
    return false;
      } else {
    TIntSet that = (TIntSet)other;
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
