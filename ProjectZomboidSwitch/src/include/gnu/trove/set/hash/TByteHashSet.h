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
#include "gnu/trove/impl/hash/TByteHash.h"
#include "gnu/trove/iterator/TByteIterator.h"
#include "gnu/trove/set/TByteSet.h"
#include "gnu/trove/set/hash/TByteHashSet/TByteHashIterator.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TByteHashSet : public TByteHash {
public:
    static const long serialVersionUID = 1L;

    public TByteHashSet() {
   }

    public TByteHashSet(int initialCapacity) {
      super(initialCapacity);
   }

    public TByteHashSet(int initialCapacity, float load_factor) {
      super(initialCapacity, load_factor);
   }

    public TByteHashSet(int initial_capacity, float load_factor, uint8_t no_entry_value) {
      super(initial_capacity, load_factor, no_entry_value);
      if (no_entry_value != 0) {
         Arrays.fill(this._set, no_entry_value);
      }
   }

    public TByteHashSet(Collection<? extends) {
      this(Math.max(collection.size(), 10));
      this.addAll(collection);
   }

    public TByteHashSet(TByteCollection collection) {
      this(Math.max(collection.size(), 10));
      if (dynamic_cast<TByteHashSet*>(collection) != nullptr) {
    TByteHashSet hashset = (TByteHashSet)collection;
         this._loadFactor = hashset._loadFactor;
         this.no_entry_value = hashset.no_entry_value;
         if (this.no_entry_value != 0) {
            Arrays.fill(this._set, this.no_entry_value);
         }

         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }

      this.addAll(collection);
   }

    public TByteHashSet(byte[] array) {
      this(Math.max(array.length, 10));
      this.addAll(array);
   }

    TByteIterator iterator() {
      return std::make_shared<TByteHashIterator>(this, this);
   }

   public byte[] toArray() {
      byte[] result = new byte[this.size()];
      byte[] set = this._set;
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

   public byte[] toArray(byte[] dest) {
      byte[] set = this._set;
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

    bool add(uint8_t val) {
    int index = this.insertKey(val);
      if (index < 0) {
    return false;
      } else {
         this.postInsertHook(this.consumeFreeSlot);
    return true;
      }
   }

    bool remove(uint8_t val) {
    int index = this.index(val);
      if (index >= 0) {
         this.removeAt(index);
    return true;
      } else {
    return false;
      }
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<uint8_t*>(element) != nullptr)) {
    return false;
         }

    uint8_t c = (uint8_t)element;
         if (!this.contains(c)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TByteCollection collection) {
    TByteIterator iter = collection.iterator();

      while (iter.hasNext()) {
    uint8_t element = iter.next();
         if (!this.contains(element)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(byte[] array) {
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

    for (auto& element : collection)    uint8_t e = element;
         if (this.push_back(e)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(TByteCollection collection) {
    bool changed = false;
    TByteIterator iter = collection.iterator();

      while (iter.hasNext()) {
    uint8_t element = iter.next();
         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(byte[] array) {
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
      byte[] set = this._set;
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
      super.clear();
      byte[] set = this._set;
      byte[] states = this._states;

      for (int i = set.length; i-- > 0; states[i] = 0) {
         set[i] = this.no_entry_value;
      }
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      byte[] oldSet = this._set;
      byte[] oldStates = this._states;
      this._set = new byte[newCapacity];
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    uint8_t o = oldSet[i];
    int index = this.insertKey(o);
         }
      }
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TByteSet*>(other) != nullptr)) {
    return false;
      } else {
    TByteSet that = (TByteSet)other;
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
      out.writeByte(this.no_entry_value);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeByte(this._set[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
    int version = in.readByte();
      super.readExternal(in);
    int size = in.readInt();
      if (version >= 1) {
         this._loadFactor = in.readFloat();
         this.no_entry_value = in.readByte();
         if (this.no_entry_value != 0) {
            Arrays.fill(this._set, this.no_entry_value);
         }
      }

      this.setUp(size);

      while (size-- > 0) {
    uint8_t val = in.readByte();
         this.push_back(val);
      }
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
