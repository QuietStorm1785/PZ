#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/map/hash/TDoubleObjectHashMap/KeyView/TDoubleHashIterator.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TDoubleObjectHashMap {
public:
   TDoubleObjectHashMap$KeyView(TDoubleObjectHashMap var1) {
      this.this$0 = var1;
   }

    double getNoEntryValue() {
      return this.this$0.no_entry_key;
   }

    int size() {
      return TDoubleObjectHashMap.access$000(this.this$0);
   }

    bool isEmpty() {
      return TDoubleObjectHashMap.access$100(this.this$0) == 0;
   }

    bool contains(double entry) {
      return this.this$0.containsKey(entry);
   }

    TDoubleIterator iterator() {
      return std::make_shared<TDoubleHashIterator>(this, this.this$0);
   }

   public double[] toArray() {
      return this.this$0.keys();
   }

   public double[] toArray(double[] dest) {
      return this.this$0.keys(dest);
   }

    bool add(double entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(double entry) {
      return nullptr != this.this$0.remove(entry);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!this.this$0.containsKey((double)element)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TDoubleCollection collection) {
      if (collection == this) {
    return true;
      } else {
    TDoubleIterator iter = collection.iterator();

         while (iter.hasNext()) {
            if (!this.this$0.containsKey(iter.next())) {
    return false;
            }
         }

    return true;
      }
   }

    bool containsAll(double[] array) {
    for (auto& element : array)         if (!this.this$0.containsKey(element)) {
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
      double[] set = this.this$0._set;
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
      if (collection == this) {
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
      return this.this$0.forEachKey(procedure);
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TDoubleSet*>(other) != nullptr)) {
    return false;
      } else {
    TDoubleSet that = (TDoubleSet)other;
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
