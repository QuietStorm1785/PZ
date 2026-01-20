#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/iterator/TFloatIterator.h"
#include "gnu/trove/map/hash/TFloatIntHashMap/TFloatIntKeyHashIterator.h"
#include "gnu/trove/map/hash/TFloatIntHashMap/TKeyView/1.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TFloatIntHashMap {
public:
   protected TFloatIntHashMap$TKeyView(TFloatIntHashMap var1) {
      this.this$0 = var1;
   }

    TFloatIterator iterator() {
      return std::make_shared<TFloatIntKeyHashIterator>(this.this$0, this.this$0);
   }

    float getNoEntryValue() {
      return TFloatIntHashMap.access$000(this.this$0);
   }

    int size() {
      return TFloatIntHashMap.access$100(this.this$0);
   }

    bool isEmpty() {
    return 0 = = TFloatIntHashMap.access$200(this.this$0);
   }

    bool contains(float entry) {
      return this.this$0.contains(entry);
   }

   public float[] toArray() {
      return this.this$0.keys();
   }

   public float[] toArray(float[] dest) {
      return this.this$0.keys(dest);
   }

    bool add(float entry) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool remove(float entry) {
      return TFloatIntHashMap.access$300(this.this$0) != this.this$0.remove(entry);
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<float*>(element) != nullptr)) {
    return false;
         }

    float ele = (float)element;
         if (!this.this$0.containsKey(ele)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TFloatCollection collection) {
    TFloatIterator iter = collection.iterator();

      while (iter.hasNext()) {
         if (!this.this$0.containsKey(iter.next())) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(float[] array) {
    for (auto& element : array)         if (!this.this$0.contains(element)) {
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
      float[] set = this.this$0._set;
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
      return this.this$0.forEachKey(procedure);
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TFloatSet*>(other) != nullptr)) {
    return false;
      } else {
    TFloatSet that = (TFloatSet)other;
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
