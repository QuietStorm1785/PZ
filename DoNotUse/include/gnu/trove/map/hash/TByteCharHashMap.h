#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/hash/TByteCharHash.h"
#include "gnu/trove/iterator/TByteCharIterator.h"
#include "gnu/trove/map/TByteCharMap.h"
#include "gnu/trove/map/hash/TByteCharHashMap/1.h"
#include "gnu/trove/map/hash/TByteCharHashMap/TByteCharHashIterator.h"
#include "gnu/trove/map/hash/TByteCharHashMap/TKeyView.h"
#include "gnu/trove/map/hash/TByteCharHashMap/TValueView.h"
#include "gnu/trove/procedure/TByteCharProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TByteCharHashMap : public TByteCharHash {
public:
    static const long serialVersionUID = 1L;
   protected transient char[] _values;

    public TByteCharHashMap() {
   }

    public TByteCharHashMap(int initialCapacity) {
      super(initialCapacity);
   }

    public TByteCharHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public TByteCharHashMap(int initialCapacity, float loadFactor, uint8_t noEntryKey, char noEntryValue) {
      super(initialCapacity, loadFactor, noEntryKey, noEntryValue);
   }

    public TByteCharHashMap(byte[] keys, char[] values) {
      super(Math.max(keys.length, values.length));
    int size = Math.min(keys.length, values.length);

      for (int i = 0; i < size; i++) {
         this.put(keys[i], values[i]);
      }
   }

    public TByteCharHashMap(TByteCharMap map) {
      super(map.size());
      if (dynamic_cast<TByteCharHashMap*>(map) != nullptr) {
    TByteCharHashMap hashmap = (TByteCharHashMap)map;
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
      this._values = new char[capacity];
    return capacity;
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      byte[] oldKeys = this._set;
      char[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new byte[newCapacity];
      this._values = new char[newCapacity];
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

    char put(uint8_t key, char value) {
    int index = this.insertKey(key);
      return this.doPut(key, value, index);
   }

    char putIfAbsent(uint8_t key, char value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(key, value, index);
   }

    char doPut(uint8_t key, char value, int index) {
    char previous = this.no_entry_value;
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

      for (Entry<? : public uint8_t, ? : public char> entry : map.entrySet()) {
         this.put(entry.getKey(), entry.getValue());
      }
   }

    void putAll(TByteCharMap map) {
      this.ensureCapacity(map.size());
    TByteCharIterator iter = map.iterator();

      while (iter.hasNext()) {
         iter.advance();
         this.put(iter.key(), iter.value());
      }
   }

    char get(uint8_t key) {
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

    char remove(uint8_t key) {
    char prev = this.no_entry_value;
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

    TCharCollection valueCollection() {
      return std::make_shared<TValueView>(this);
   }

   public char[] values() {
      char[] vals = new char[this.size()];
      char[] v = this._values;
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

   public char[] values(char[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new char[size];
      }

      char[] v = this._values;
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

    bool containsValue(char val) {
      byte[] states = this._states;
      char[] vals = this._values;
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

    TByteCharIterator iterator() {
      return std::make_shared<TByteCharHashIterator>(this, this);
   }

    bool forEachKey(TByteProcedure procedure) {
      return this.forEach(procedure);
   }

    bool forEachValue(TCharProcedure procedure) {
      byte[] states = this._states;
      char[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TByteCharProcedure procedure) {
      byte[] states = this._states;
      byte[] keys = this._set;
      char[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    void transformValues(TCharFunction function) {
      byte[] states = this._states;
      char[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            values[i] = function.execute(values[i]);
         }
      }
   }

    bool retainEntries(TByteCharProcedure procedure) {
    bool modified = false;
      byte[] states = this._states;
      byte[] keys = this._set;
      char[] values = this._values;
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
      return this.adjustValue(key, '\u0001');
   }

    bool adjustValue(uint8_t key, char amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = (char)(this._values[index] + amount);
    return true;
      }
   }

    char adjustOrPutValue(uint8_t key, char adjust_amount, char put_amount) {
    int index = this.insertKey(key);
    bool isNewMapping;
    char newValue;
      if (index < 0) {
         index = -index - 1;
         newValue = this._values[index] = (char)(this._values[index] + adjust_amount);
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
      if (!(dynamic_cast<TByteCharMap*>(other) != nullptr)) {
    return false;
      } else {
    TByteCharMap that = (TByteCharMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            char[] values = this._values;
            byte[] states = this._states;
    char this_no_entry_value = this.getNoEntryValue();
    char that_no_entry_value = that.getNoEntryValue();
    int i = values.length;

            while (i-- > 0) {
               if (states[i] == 1) {
    uint8_t key = this._set[i];
    char that_value = that.get(key);
    char this_value = values[i];
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
            out.writeChar(this._values[i]);
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
    char val = in.readChar();
         this.put(key, val);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
