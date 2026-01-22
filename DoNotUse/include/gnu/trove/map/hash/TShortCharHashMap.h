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
#include "gnu/trove/impl/hash/TShortCharHash.h"
#include "gnu/trove/iterator/TShortCharIterator.h"
#include "gnu/trove/map/TShortCharMap.h"
#include "gnu/trove/map/hash/TShortCharHashMap/1.h"
#include "gnu/trove/map/hash/TShortCharHashMap/TKeyView.h"
#include "gnu/trove/map/hash/TShortCharHashMap/TShortCharHashIterator.h"
#include "gnu/trove/map/hash/TShortCharHashMap/TValueView.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TShortCharProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TShortCharHashMap : public TShortCharHash {
public:
    static const long serialVersionUID = 1L;
   protected transient char[] _values;

    public TShortCharHashMap() {
   }

    public TShortCharHashMap(int initialCapacity) {
      super(initialCapacity);
   }

    public TShortCharHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public TShortCharHashMap(int initialCapacity, float loadFactor, short noEntryKey, char noEntryValue) {
      super(initialCapacity, loadFactor, noEntryKey, noEntryValue);
   }

    public TShortCharHashMap(short[] keys, char[] values) {
      super(Math.max(keys.length, values.length));
    int size = Math.min(keys.length, values.length);

      for (int i = 0; i < size; i++) {
         this.put(keys[i], values[i]);
      }
   }

    public TShortCharHashMap(TShortCharMap map) {
      super(map.size());
      if (dynamic_cast<TShortCharHashMap*>(map) != nullptr) {
    TShortCharHashMap hashmap = (TShortCharHashMap)map;
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
      short[] oldKeys = this._set;
      char[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new short[newCapacity];
      this._values = new char[newCapacity];
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    short o = oldKeys[i];
    int index = this.insertKey(o);
            this._values[index] = oldVals[i];
         }
      }
   }

    char put(short key, char value) {
    int index = this.insertKey(key);
      return this.doPut(key, value, index);
   }

    char putIfAbsent(short key, char value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(key, value, index);
   }

    char doPut(short key, char value, int index) {
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

      for (Entry<? : public int16_t, ? : public char> entry : map.entrySet()) {
         this.put(entry.getKey(), entry.getValue());
      }
   }

    void putAll(TShortCharMap map) {
      this.ensureCapacity(map.size());
    TShortCharIterator iter = map.iterator();

      while (iter.hasNext()) {
         iter.advance();
         this.put(iter.key(), iter.value());
      }
   }

    char get(short key) {
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

    char remove(short key) {
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

    TShortSet keySet() {
      return std::make_shared<TKeyView>(this);
   }

   public short[] keys() {
      short[] keys = new short[this.size()];
      short[] k = this._set;
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

   public short[] keys(short[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new short[size];
      }

      short[] keys = this._set;
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

    bool containsKey(short key) {
      return this.contains(key);
   }

    TShortCharIterator iterator() {
      return std::make_shared<TShortCharHashIterator>(this, this);
   }

    bool forEachKey(TShortProcedure procedure) {
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

    bool forEachEntry(TShortCharProcedure procedure) {
      byte[] states = this._states;
      short[] keys = this._set;
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

    bool retainEntries(TShortCharProcedure procedure) {
    bool modified = false;
      byte[] states = this._states;
      short[] keys = this._set;
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

    bool increment(short key) {
      return this.adjustValue(key, '\u0001');
   }

    bool adjustValue(short key, char amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = (char)(this._values[index] + amount);
    return true;
      }
   }

    char adjustOrPutValue(short key, char adjust_amount, char put_amount) {
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
      if (!(dynamic_cast<TShortCharMap*>(other) != nullptr)) {
    return false;
      } else {
    TShortCharMap that = (TShortCharMap)other;
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
    short key = this._set[i];
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
            out.writeShort(this._set[i]);
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
    short key = in.readShort();
    char val = in.readChar();
         this.put(key, val);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
