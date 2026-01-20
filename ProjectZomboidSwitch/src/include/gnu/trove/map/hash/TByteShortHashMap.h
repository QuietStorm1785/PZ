#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/hash/TByteShortHash.h"
#include "gnu/trove/iterator/TByteShortIterator.h"
#include "gnu/trove/map/TByteShortMap.h"
#include "gnu/trove/map/hash/TByteShortHashMap/1.h"
#include "gnu/trove/map/hash/TByteShortHashMap/TByteShortHashIterator.h"
#include "gnu/trove/map/hash/TByteShortHashMap/TKeyView.h"
#include "gnu/trove/map/hash/TByteShortHashMap/TValueView.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TByteShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TByteShortHashMap : public TByteShortHash {
public:
    static const long serialVersionUID = 1L;
   protected transient short[] _values;

    public TByteShortHashMap() {
   }

    public TByteShortHashMap(int initialCapacity) {
      super(initialCapacity);
   }

    public TByteShortHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public TByteShortHashMap(int initialCapacity, float loadFactor, uint8_t noEntryKey, short noEntryValue) {
      super(initialCapacity, loadFactor, noEntryKey, noEntryValue);
   }

    public TByteShortHashMap(byte[] keys, short[] values) {
      super(Math.max(keys.length, values.length));
    int size = Math.min(keys.length, values.length);

      for (int i = 0; i < size; i++) {
         this.put(keys[i], values[i]);
      }
   }

    public TByteShortHashMap(TByteShortMap map) {
      super(map.size());
      if (dynamic_cast<TByteShortHashMap*>(map) != nullptr) {
    TByteShortHashMap hashmap = (TByteShortHashMap)map;
         this._loadFactor = hashmap._loadFactor;
         this.no_entry_key = hashmap.no_entry_key;
         this.no_entry_value = hashmap.no_entry_value;
         if (this.no_entry_key != 0) {
            Arrays.fill(this._set, this.no_entry_key);
         }

         if (this.no_entry_value != 0) {
            Arrays.fill(this._values, this.no_entry_value);
         }

         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }

      this.putAll(map);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._values = new short[capacity];
    return capacity;
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      byte[] oldKeys = this._set;
      short[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new byte[newCapacity];
      this._values = new short[newCapacity];
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    uint8_t o = oldKeys[i];
    int index = this.insertKey(o);
            this._values[index] = oldVals[i];
         }
      }
   }

    short put(uint8_t key, short value) {
    int index = this.insertKey(key);
      return this.doPut(key, value, index);
   }

    short putIfAbsent(uint8_t key, short value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(key, value, index);
   }

    short doPut(uint8_t key, short value, int index) {
    short previous = this.no_entry_value;
    bool isNewMapping = true;
      if (index < 0) {
         index = -index - 1;
         previous = this._values[index];
         isNewMapping = false;
      }

      this._values[index] = value;
      if (isNewMapping) {
         this.postInsertHook(this.consumeFreeSlot);
      }

    return previous;
   }

    void putAll(Map<? extends, ? extends) {
      this.ensureCapacity(map.size());

      for (Entry<? : public uint8_t, ? : public int16_t> entry : map.entrySet()) {
         this.put(entry.getKey(), entry.getValue());
      }
   }

    void putAll(TByteShortMap map) {
      this.ensureCapacity(map.size());
    TByteShortIterator iter = map.iterator();

      while (iter.hasNext()) {
         iter.advance();
         this.put(iter.key(), iter.value());
      }
   }

    short get(uint8_t key) {
    int index = this.index(key);
      return index < 0 ? this.no_entry_value : this._values[index];
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, this.no_entry_key);
      Arrays.fill(this._values, 0, this._values.length, this.no_entry_value);
      Arrays.fill(this._states, 0, this._states.length, (byte)0);
   }

    bool isEmpty() {
    return 0 = = this._size;
   }

    short remove(uint8_t key) {
    short prev = this.no_entry_value;
    int index = this.index(key);
      if (index >= 0) {
         prev = this._values[index];
         this.removeAt(index);
      }

    return prev;
   }

    void removeAt(int index) {
      this._values[index] = this.no_entry_value;
      super.removeAt(index);
   }

    TByteSet keySet() {
      return std::make_shared<TKeyView>(this);
   }

   public byte[] keys() {
      byte[] keys = new byte[this.size()];
      byte[] k = this._set;
      byte[] states = this._states;
    int i = k.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            keys[j++] = k[i];
         }
      }

    return keys;
   }

   public byte[] keys(byte[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new byte[size];
      }

      byte[] keys = this._set;
      byte[] states = this._states;
    int i = keys.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            array[j++] = keys[i];
         }
      }

    return array;
   }

    TShortCollection valueCollection() {
      return std::make_shared<TValueView>(this);
   }

   public short[] values() {
      short[] vals = new short[this.size()];
      short[] v = this._values;
      byte[] states = this._states;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            vals[j++] = v[i];
         }
      }

    return vals;
   }

   public short[] values(short[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new short[size];
      }

      short[] v = this._values;
      byte[] states = this._states;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (states[i] == 1) {
            array[j++] = v[i];
         }
      }

    return array;
   }

    bool containsValue(short val) {
      byte[] states = this._states;
      short[] vals = this._values;
    int i = vals.length;

      while (i-- > 0) {
         if (states[i] == 1 && val == vals[i]) {
    return true;
         }
      }

    return false;
   }

    bool containsKey(uint8_t key) {
      return this.contains(key);
   }

    TByteShortIterator iterator() {
      return std::make_shared<TByteShortHashIterator>(this, this);
   }

    bool forEachKey(TByteProcedure procedure) {
      return this.forEach(procedure);
   }

    bool forEachValue(TShortProcedure procedure) {
      byte[] states = this._states;
      short[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TByteShortProcedure procedure) {
      byte[] states = this._states;
      byte[] keys = this._set;
      short[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    void transformValues(TShortFunction function) {
      byte[] states = this._states;
      short[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            values[i] = function.execute(values[i]);
         }
      }
   }

    bool retainEntries(TByteShortProcedure procedure) {
    bool modified = false;
      byte[] states = this._states;
      byte[] keys = this._set;
      short[] values = this._values;
      this.tempDisableAutoCompaction();

      try {
    int i = keys.length;

         while (i-- > 0) {
            if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
               this.removeAt(i);
               modified = true;
            }
         }
      } finally {
         this.reenableAutoCompaction(true);
      }

    return modified;
   }

    bool increment(uint8_t key) {
      return this.adjustValue(key, (short)1);
   }

    bool adjustValue(uint8_t key, short amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = (short)(this._values[index] + amount);
    return true;
      }
   }

    short adjustOrPutValue(uint8_t key, short adjust_amount, short put_amount) {
    int index = this.insertKey(key);
    bool isNewMapping;
    short newValue;
      if (index < 0) {
         index = -index - 1;
         newValue = this._values[index] = (short)(this._values[index] + adjust_amount);
         isNewMapping = false;
      } else {
         newValue = this._values[index] = put_amount;
         isNewMapping = true;
      }

    uint8_t previousState = this._states[index];
      if (isNewMapping) {
         this.postInsertHook(this.consumeFreeSlot);
      }

    return newValue;
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TByteShortMap*>(other) != nullptr)) {
    return false;
      } else {
    TByteShortMap that = (TByteShortMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            short[] values = this._values;
            byte[] states = this._states;
    short this_no_entry_value = this.getNoEntryValue();
    short that_no_entry_value = that.getNoEntryValue();
    int i = values.length;

            while (i-- > 0) {
               if (states[i] == 1) {
    uint8_t key = this._set[i];
    short that_value = that.get(key);
    short this_value = values[i];
                  if (this_value != that_value && this_value != this_no_entry_value && that_value != that_no_entry_value) {
    return false;
                  }
               }
            }

    return true;
         }
      }
   }

    int hashCode() {
    int hashcode = 0;
      byte[] states = this._states;
    int i = this._values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            hashcode += HashFunctions.hash(this._set[i]) ^ HashFunctions.hash(this._values[i]);
         }
      }

    return hashcode;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.forEachEntry(std::make_shared<1>(this, buf));
      buf.append("}");
      return buf;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
      out.writeInt(this._size);
    int i = this._states.length;

      while (i-- > 0) {
         if (this._states[i] == 1) {
            out.writeByte(this._set[i]);
            out.writeShort(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    uint8_t key = in.readByte();
    short val = in.readShort();
         this.put(key, val);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
