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
#include "gnu/trove/impl/hash/TDoubleHash.h"
#include "gnu/trove/iterator/TDoubleIterator.h"
#include "gnu/trove/set/TDoubleSet.h"
#include "gnu/trove/set/hash/TDoubleHashSet/TDoubleHashIterator.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TDoubleHashSet : public TDoubleHash {
public:
    static const long serialVersionUID = 1L;

    public TDoubleHashSet() {
   }

    public TDoubleHashSet(int initialCapacity) {
      super(initialCapacity);
   }

    public TDoubleHashSet(int initialCapacity, float load_factor) {
      super(initialCapacity, load_factor);
   }

    public TDoubleHashSet(int initial_capacity, float load_factor, double no_entry_value) {
      super(initial_capacity, load_factor, no_entry_value);
      if (no_entry_value != 0.0) {
         Arrays.fill(this._set, no_entry_value);
      }
   }

    public TDoubleHashSet(Collection<? extends) {
      this(Math.max(collection.size(), 10));
      this.addAll(collection);
   }

    public TDoubleHashSet(TDoubleCollection collection) {
      this(Math.max(collection.size(), 10));
      if (dynamic_cast<TDoubleHashSet*>(collection) != nullptr) {
    TDoubleHashSet hashset = (TDoubleHashSet)collection;
         this._loadFactor = hashset._loadFactor;
         this.no_entry_value = hashset.no_entry_value;
         if (this.no_entry_value != 0.0) {
            Arrays.fill(this._set, this.no_entry_value);
         }

         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }

      this.addAll(collection);
   }

    public TDoubleHashSet(double[] array) {
      this(Math.max(array.length, 10));
      this.addAll(array);
   }

    TDoubleIterator iterator() {
      return std::make_shared<TDoubleHashIterator>(this, this);
   }

   public double[] toArray() {
      double[] result = new double[this.size()];
      double[] set = this._set;
      byte[] states = this._states;
    int i = states.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            result[j++] = set[i];
         }
      }

    return result;
   }

   public double[] toArray(double[] dest) {
      double[] set = this._set;
      byte[] states = this._states;
    int i = states.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            dest[j++] = set[i];
         }
      }

      if (dest.length > this._size) {
         dest[this._size] = this.no_entry_value;
      }

    return dest;
   }

    bool add(double val) {
    int index = this.insertKey(val);
      if (index < 0) {
    return false;
      } else {
         this.postInsertHook(this.consumeFreeSlot);
    return true;
      }
   }

    bool remove(double val) {
    int index = this.index(val);
      if (index >= 0) {
         this.removeAt(index);
    return true;
      } else {
    return false;
      }
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<double*>(element) != nullptr)) {
    return false;
         }

    double c = (double)element;
         if (!this.contains(c)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TDoubleCollection collection) {
    TDoubleIterator iter = collection.iterator();

      while (iter.hasNext()) {
    double element = iter.next();
         if (!this.contains(element)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(double[] array) {
    int i = array.length;

      while (i-- > 0) {
         if (!this.contains(array[i])) {
    return false;
         }
      }

    return true;
   }

    bool addAll(Collection<? extends) {
    bool changed = false;

    for (auto& element : collection)    double e = element;
         if (this.push_back(e)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(TDoubleCollection collection) {
    bool changed = false;
    TDoubleIterator iter = collection.iterator();

      while (iter.hasNext()) {
    double element = iter.next();
         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(double[] array) {
    bool changed = false;
    int i = array.length;

      while (i-- > 0) {
         if (this.push_back(array[i])) {
            changed = true;
         }
      }

    return changed;
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
      double[] set = this._set;
      byte[] states = this._states;
      this._autoCompactTemporaryDisable = true;
    int i = set.length;

      while (i-- > 0) {
         if (states[i] == 1 && Arrays.binarySearch(array, set[i]) < 0) {
            this.removeAt(i);
            changed = true;
         }
      }

      this._autoCompactTemporaryDisable = false;
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
      super.clear();
      double[] set = this._set;
      byte[] states = this._states;

      for (int i = set.length; i-- > 0; states[i] = 0) {
         set[i] = this.no_entry_value;
      }
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      double[] oldSet = this._set;
      byte[] oldStates = this._states;
      this._set = new double[newCapacity];
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    double o = oldSet[i];
    int index = this.insertKey(o);
         }
      }
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TDoubleSet*>(other) != nullptr)) {
    return false;
      } else {
    TDoubleSet that = (TDoubleSet)other;
         if (that.size() != this.size()) {
    return false;
         } else {
    int i = this._states.length;

            while (i-- > 0) {
               if (this._states[i] == 1 && !that.contains(this._set[i])) {
    return false;
               }
            }

    return true;
         }
      }
   }

    int hashCode() {
    int hashcode = 0;
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            hashcode += HashFunctions.hash(this._set[i]);
         }
      }

    return hashcode;
   }

    std::string toString() {
    std::stringstream buffy = new std::stringstream(this._size * 2 + 2);
      buffy.append("{");
    int i = this._states.length;
    int j = 1;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            buffy.append(this._set[i]);
            if (j++ < this._size) {
               buffy.append(",");
            }
         }
      }

      buffy.append("}");
      return buffy;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(1);
      super.writeExternal(out);
      out.writeInt(this._size);
      out.writeFloat(this._loadFactor);
      out.writeDouble(this.no_entry_value);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeDouble(this._set[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
    int version = in.readByte();
      super.readExternal(in);
    int size = in.readInt();
      if (version >= 1) {
         this._loadFactor = in.readFloat();
         this.no_entry_value = in.readDouble();
         if (this.no_entry_value != 0.0) {
            Arrays.fill(this._set, this.no_entry_value);
         }
      }

      this.setUp(size);

      while (size-- > 0) {
    double val = in.readDouble();
         this.push_back(val);
      }
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
