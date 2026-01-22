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
#include "gnu/trove/impl/hash/TLongHash.h"
#include "gnu/trove/iterator/TLongIterator.h"
#include "gnu/trove/set/TLongSet.h"
#include "gnu/trove/set/hash/TLongHashSet/TLongHashIterator.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TLongHashSet : public TLongHash {
public:
    static const long serialVersionUID = 1L;

    public TLongHashSet() {
   }

    public TLongHashSet(int initialCapacity) {
      super(initialCapacity);
   }

    public TLongHashSet(int initialCapacity, float load_factor) {
      super(initialCapacity, load_factor);
   }

    public TLongHashSet(int initial_capacity, float load_factor, long no_entry_value) {
      super(initial_capacity, load_factor, no_entry_value);
      if (no_entry_value != 0L) {
         Arrays.fill(this._set, no_entry_value);
      }
   }

    public TLongHashSet(Collection<? extends) {
      this(Math.max(collection.size(), 10));
      this.addAll(collection);
   }

    public TLongHashSet(TLongCollection collection) {
      this(Math.max(collection.size(), 10));
      if (dynamic_cast<TLongHashSet*>(collection) != nullptr) {
    TLongHashSet hashset = (TLongHashSet)collection;
         this._loadFactor = hashset._loadFactor;
         this.no_entry_value = hashset.no_entry_value;
         if (this.no_entry_value != 0L) {
            Arrays.fill(this._set, this.no_entry_value);
         }

         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }

      this.addAll(collection);
   }

    public TLongHashSet(long[] array) {
      this(Math.max(array.length, 10));
      this.addAll(array);
   }

    TLongIterator iterator() {
      return std::make_shared<TLongHashIterator>(this, this);
   }

   public long[] toArray() {
      long[] result = new long[this.size()];
      long[] set = this._set;
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

   public long[] toArray(long[] dest) {
      long[] set = this._set;
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

    bool add(long val) {
    int index = this.insertKey(val);
      if (index < 0) {
    return false;
      } else {
         this.postInsertHook(this.consumeFreeSlot);
    return true;
      }
   }

    bool remove(long val) {
    int index = this.index(val);
      if (index >= 0) {
         this.removeAt(index);
    return true;
      } else {
    return false;
      }
   }

    bool containsAll(Collection<?> collection) {
    for (auto& element : collection)         if (!(dynamic_cast<int64_t*>(element) != nullptr)) {
    return false;
         }

    long c = (int64_t)element;
         if (!this.contains(c)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(TLongCollection collection) {
    TLongIterator iter = collection.iterator();

      while (iter.hasNext()) {
    long element = iter.next();
         if (!this.contains(element)) {
    return false;
         }
      }

    return true;
   }

    bool containsAll(long[] array) {
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

    for (auto& element : collection)    long e = element;
         if (this.push_back(e)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(TLongCollection collection) {
    bool changed = false;
    TLongIterator iter = collection.iterator();

      while (iter.hasNext()) {
    long element = iter.next();
         if (this.push_back(element)) {
            changed = true;
         }
      }

    return changed;
   }

    bool addAll(long[] array) {
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
      long[] set = this._set;
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
      super.clear();
      long[] set = this._set;
      byte[] states = this._states;

      for (int i = set.length; i-- > 0; states[i] = 0) {
         set[i] = this.no_entry_value;
      }
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      long[] oldSet = this._set;
      byte[] oldStates = this._states;
      this._set = new long[newCapacity];
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    long o = oldSet[i];
    int index = this.insertKey(o);
         }
      }
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TLongSet*>(other) != nullptr)) {
    return false;
      } else {
    TLongSet that = (TLongSet)other;
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
      out.writeLong(this.no_entry_value);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeLong(this._set[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
    int version = in.readByte();
      super.readExternal(in);
    int size = in.readInt();
      if (version >= 1) {
         this._loadFactor = in.readFloat();
         this.no_entry_value = in.readLong();
         if (this.no_entry_value != 0L) {
            Arrays.fill(this._set, this.no_entry_value);
         }
      }

      this.setUp(size);

      while (size-- > 0) {
    long val = in.readLong();
         this.push_back(val);
      }
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
