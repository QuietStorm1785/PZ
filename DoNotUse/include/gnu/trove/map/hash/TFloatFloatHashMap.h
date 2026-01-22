#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/hash/TFloatFloatHash.h"
#include "gnu/trove/iterator/TFloatFloatIterator.h"
#include "gnu/trove/map/TFloatFloatMap.h"
#include "gnu/trove/map/hash/TFloatFloatHashMap/1.h"
#include "gnu/trove/map/hash/TFloatFloatHashMap/TFloatFloatHashIterator.h"
#include "gnu/trove/map/hash/TFloatFloatHashMap/TKeyView.h"
#include "gnu/trove/map/hash/TFloatFloatHashMap/TValueView.h"
#include "gnu/trove/procedure/TFloatFloatProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TFloatFloatHashMap : public TFloatFloatHash {
public:
    static const long serialVersionUID = 1L;
   protected transient float[] _values;

    public TFloatFloatHashMap() {
   }

    public TFloatFloatHashMap(int initialCapacity) {
      super(initialCapacity);
   }

    public TFloatFloatHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
   }

    public TFloatFloatHashMap(int initialCapacity, float loadFactor, float noEntryKey, float noEntryValue) {
      super(initialCapacity, loadFactor, noEntryKey, noEntryValue);
   }

    public TFloatFloatHashMap(float[] keys, float[] values) {
      super(Math.max(keys.length, values.length));
    int size = Math.min(keys.length, values.length);

      for (int i = 0; i < size; i++) {
         this.put(keys[i], values[i]);
      }
   }

    public TFloatFloatHashMap(TFloatFloatMap map) {
      super(map.size());
      if (dynamic_cast<TFloatFloatHashMap*>(map) != nullptr) {
    TFloatFloatHashMap hashmap = (TFloatFloatHashMap)map;
         this._loadFactor = hashmap._loadFactor;
         this.no_entry_key = hashmap.no_entry_key;
         this.no_entry_value = hashmap.no_entry_value;
         if (this.no_entry_key != 0.0F) {
            Arrays.fill(this._set, this.no_entry_key);
         }

         if (this.no_entry_value != 0.0F) {
            Arrays.fill(this._values, this.no_entry_value);
         }

         this.setUp((int)Math.ceil(10.0F / this._loadFactor));
      }

      this.putAll(map);
   }

    int setUp(int initialCapacity) {
    int capacity = super.setUp(initialCapacity);
      this._values = new float[capacity];
    return capacity;
   }

    void rehash(int newCapacity) {
    int oldCapacity = this._set.length;
      float[] oldKeys = this._set;
      float[] oldVals = this._values;
      byte[] oldStates = this._states;
      this._set = new float[newCapacity];
      this._values = new float[newCapacity];
      this._states = new byte[newCapacity];
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldStates[i] == 1) {
    float o = oldKeys[i];
    int index = this.insertKey(o);
            this._values[index] = oldVals[i];
         }
      }
   }

    float put(float key, float value) {
    int index = this.insertKey(key);
      return this.doPut(key, value, index);
   }

    float putIfAbsent(float key, float value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(key, value, index);
   }

    float doPut(float key, float value, int index) {
    float previous = this.no_entry_value;
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

      for (Entry<? : public float, ? : public float> entry : map.entrySet()) {
         this.put(entry.getKey(), entry.getValue());
      }
   }

    void putAll(TFloatFloatMap map) {
      this.ensureCapacity(map.size());
    TFloatFloatIterator iter = map.iterator();

      while (iter.hasNext()) {
         iter.advance();
         this.put(iter.key(), iter.value());
      }
   }

    float get(float key) {
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

    float remove(float key) {
    float prev = this.no_entry_value;
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

    TFloatSet keySet() {
      return std::make_shared<TKeyView>(this);
   }

   public float[] keys() {
      float[] keys = new float[this.size()];
      float[] k = this._set;
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

   public float[] keys(float[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new float[size];
      }

      float[] keys = this._set;
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

    TFloatCollection valueCollection() {
      return std::make_shared<TValueView>(this);
   }

   public float[] values() {
      float[] vals = new float[this.size()];
      float[] v = this._values;
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

   public float[] values(float[] array) {
    int size = this.size();
      if (array.length < size) {
         array = new float[size];
      }

      float[] v = this._values;
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

    bool containsValue(float val) {
      byte[] states = this._states;
      float[] vals = this._values;
    int i = vals.length;

      while (i-- > 0) {
         if (states[i] == 1 && val == vals[i]) {
    return true;
         }
      }

    return false;
   }

    bool containsKey(float key) {
      return this.contains(key);
   }

    TFloatFloatIterator iterator() {
      return std::make_shared<TFloatFloatHashIterator>(this, this);
   }

    bool forEachKey(TFloatProcedure procedure) {
      return this.forEach(procedure);
   }

    bool forEachValue(TFloatProcedure procedure) {
      byte[] states = this._states;
      float[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TFloatFloatProcedure procedure) {
      byte[] states = this._states;
      float[] keys = this._set;
      float[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (states[i] == 1 && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    void transformValues(TFloatFunction function) {
      byte[] states = this._states;
      float[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (states[i] == 1) {
            values[i] = function.execute(values[i]);
         }
      }
   }

    bool retainEntries(TFloatFloatProcedure procedure) {
    bool modified = false;
      byte[] states = this._states;
      float[] keys = this._set;
      float[] values = this._values;
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

    bool increment(float key) {
      return this.adjustValue(key, 1.0F);
   }

    bool adjustValue(float key, float amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = this._values[index] + amount;
    return true;
      }
   }

    float adjustOrPutValue(float key, float adjust_amount, float put_amount) {
    int index = this.insertKey(key);
    bool isNewMapping;
    float newValue;
      if (index < 0) {
         index = -index - 1;
         newValue = this._values[index] = this._values[index] + adjust_amount;
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
      if (!(dynamic_cast<TFloatFloatMap*>(other) != nullptr)) {
    return false;
      } else {
    TFloatFloatMap that = (TFloatFloatMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            float[] values = this._values;
            byte[] states = this._states;
    float this_no_entry_value = this.getNoEntryValue();
    float that_no_entry_value = that.getNoEntryValue();
    int i = values.length;

            while (i-- > 0) {
               if (states[i] == 1) {
    float key = this._set[i];
    float that_value = that.get(key);
    float this_value = values[i];
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
            out.writeFloat(this._set[i]);
            out.writeFloat(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    float key = in.readFloat();
    float val = in.readFloat();
         this.put(key, val);
      }
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
