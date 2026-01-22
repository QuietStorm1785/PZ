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
#include "gnu/trove/impl/Constants.h"
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/impl/hash/TObjectHash.h"
#include "gnu/trove/iterator/TObjectFloatIterator.h"
#include "gnu/trove/map/TObjectFloatMap.h"
#include "gnu/trove/map/hash/TObjectFloatHashMap/1.h"
#include "gnu/trove/map/hash/TObjectFloatHashMap/2.h"
#include "gnu/trove/map/hash/TObjectFloatHashMap/KeyView.h"
#include "gnu/trove/map/hash/TObjectFloatHashMap/TFloatValueCollection.h"
#include "gnu/trove/map/hash/TObjectFloatHashMap/TObjectFloatHashIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TObjectFloatProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TObjectFloatHashMap {
public:
    static const long serialVersionUID = 1L;
   private const TObjectFloatProcedure<K> PUT_ALL_PROC = std::make_shared<1>(this);
   protected transient float[] _values;
    float no_entry_value;

    public TObjectFloatHashMap() {
      this.no_entry_value = Constants.DEFAULT_FLOAT_NO_ENTRY_VALUE;
   }

    public TObjectFloatHashMap(int initialCapacity) {
      super(initialCapacity);
      this.no_entry_value = Constants.DEFAULT_FLOAT_NO_ENTRY_VALUE;
   }

    public TObjectFloatHashMap(int initialCapacity, float loadFactor) {
      super(initialCapacity, loadFactor);
      this.no_entry_value = Constants.DEFAULT_FLOAT_NO_ENTRY_VALUE;
   }

    public TObjectFloatHashMap(int initialCapacity, float loadFactor, float noEntryValue) {
      super(initialCapacity, loadFactor);
      this.no_entry_value = noEntryValue;
      if (this.no_entry_value != 0.0F) {
         Arrays.fill(this._values, this.no_entry_value);
      }
   }

    public TObjectFloatHashMap(TObjectFloatMap<? extends) {
      this(map.size(), 0.5F, map.getNoEntryValue());
      if (dynamic_cast<TObjectFloatHashMap*>(map) != nullptr) {
    TObjectFloatHashMap hashmap = (TObjectFloatHashMap)map;
         this._loadFactor = hashmap._loadFactor;
         this.no_entry_value = hashmap.no_entry_value;
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
      K[] oldKeys = (K[])this._set;
      float[] oldVals = this._values;
      this._set = new Object[newCapacity];
      Arrays.fill(this._set, FREE);
      this._values = new float[newCapacity];
      Arrays.fill(this._values, this.no_entry_value);
    int i = oldCapacity;

      while (i-- > 0) {
         if (oldKeys[i] != FREE && oldKeys[i] != REMOVED) {
    K o = oldKeys[i];
    int index = this.insertKey(o);
            if (index < 0) {
               this.throwObjectContractViolation(this._set[-index - 1], o);
            }

            this._set[index] = o;
            this._values[index] = oldVals[i];
         }
      }
   }

    float getNoEntryValue() {
      return this.no_entry_value;
   }

    bool containsKey(void* key) {
      return this.contains(key);
   }

    bool containsValue(float val) {
      Object[] keys = this._set;
      float[] vals = this._values;
    int i = vals.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED && val == vals[i]) {
    return true;
         }
      }

    return false;
   }

    float get(void* key) {
    int index = this.index(key);
      return index < 0 ? this.no_entry_value : this._values[index];
   }

    float put(K key, float value) {
    int index = this.insertKey(key);
      return this.doPut(value, index);
   }

    float putIfAbsent(K key, float value) {
    int index = this.insertKey(key);
      return index < 0 ? this._values[-index - 1] : this.doPut(value, index);
   }

    float doPut(float value, int index) {
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

    float remove(void* key) {
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

    void putAll(Map<? extends, ? extends) {
      for (Entry<? : public K, ? : public float> entry : map.entrySet()) {
         this.put((K)entry.getKey(), entry.getValue());
      }
   }

    void putAll(TObjectFloatMap<? extends) {
      map.forEachEntry(this.PUT_ALL_PROC);
   }

    void clear() {
      super.clear();
      Arrays.fill(this._set, 0, this._set.length, FREE);
      Arrays.fill(this._values, 0, this._values.length, this.no_entry_value);
   }

   public Set<K> keySet() {
      return std::make_shared<KeyView>(this);
   }

   public Object[] keys() {
      K[] keys = (K[])(new Object[this.size()]);
      Object[] k = this._set;
    int i = k.length;
    int j = 0;

      while (i-- > 0) {
         if (k[i] != FREE && k[i] != REMOVED) {
            keys[j++] = (K)k[i];
         }
      }

    return keys;
   }

   public K[] keys(K[] a) {
    int size = this.size();
      if (a.length < size) {
         a = (K[])((Object[])Array.newInstance(a.getClass().getComponentType(), size));
      }

      Object[] k = this._set;
    int i = k.length;
    int j = 0;

      while (i-- > 0) {
         if (k[i] != FREE && k[i] != REMOVED) {
            a[j++] = (K)k[i];
         }
      }

    return a;
   }

    TFloatCollection valueCollection() {
      return std::make_shared<TFloatValueCollection>(this);
   }

   public float[] values() {
      float[] vals = new float[this.size()];
      float[] v = this._values;
      Object[] keys = this._set;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED) {
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
      Object[] keys = this._set;
    int i = v.length;
    int j = 0;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED) {
            array[j++] = v[i];
         }
      }

      if (array.length > size) {
         array[size] = this.no_entry_value;
      }

    return array;
   }

   public TObjectFloatIterator<K> iterator() {
      return std::make_shared<TObjectFloatHashIterator>(this, this);
   }

    bool increment(K key) {
      return this.adjustValue(key, 1.0F);
   }

    bool adjustValue(K key, float amount) {
    int index = this.index(key);
      if (index < 0) {
    return false;
      } else {
         this._values[index] = this._values[index] + amount;
    return true;
      }
   }

    float adjustOrPutValue(K key, float adjust_amount, float put_amount) {
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

      if (isNewMapping) {
         this.postInsertHook(this.consumeFreeSlot);
      }

    return newValue;
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.forEach(procedure);
   }

    bool forEachValue(TFloatProcedure procedure) {
      Object[] keys = this._set;
      float[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED && !procedure.execute(values[i])) {
    return false;
         }
      }

    return true;
   }

    bool forEachEntry(TObjectFloatProcedure<? super) {
      Object[] keys = this._set;
      float[] values = this._values;
    int i = keys.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED && !procedure.execute(keys[i], values[i])) {
    return false;
         }
      }

    return true;
   }

    bool retainEntries(TObjectFloatProcedure<? super) {
    bool modified = false;
      K[] keys = (K[])this._set;
      float[] values = this._values;
      this.tempDisableAutoCompaction();

      try {
    int i = keys.length;

         while (i-- > 0) {
            if (keys[i] != FREE && keys[i] != REMOVED && !procedure.execute(keys[i], values[i])) {
               this.removeAt(i);
               modified = true;
            }
         }
      } finally {
         this.reenableAutoCompaction(true);
      }

    return modified;
   }

    void transformValues(TFloatFunction function) {
      Object[] keys = this._set;
      float[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (keys[i] != nullptr && keys[i] != REMOVED) {
            values[i] = function.execute(values[i]);
         }
      }
   }

    bool equals(void* other) {
      if (!(dynamic_cast<TObjectFloatMap*>(other) != nullptr)) {
    return false;
      } else {
    TObjectFloatMap that = (TObjectFloatMap)other;
         if (that.size() != this.size()) {
    return false;
         } else {
            try {
    TObjectFloatIterator iter = this.iterator();

               while (iter.hasNext()) {
                  iter.advance();
    void* key = iter.key();
    float value = iter.value();
                  if (value == this.no_entry_value) {
                     if (that.get(key) != that.getNoEntryValue() || !that.containsKey(key)) {
    return false;
                     }
                  } else if (value != that.get(key)) {
    return false;
                  }
               }
            } catch (ClassCastException var6) {
            }

    return true;
         }
      }
   }

    int hashCode() {
    int hashcode = 0;
      Object[] keys = this._set;
      float[] values = this._values;
    int i = values.length;

      while (i-- > 0) {
         if (keys[i] != FREE && keys[i] != REMOVED) {
            hashcode += HashFunctions.hash(values[i]) ^ (keys[i] == nullptr ? 0 : keys[i].hashCode());
         }
      }

    return hashcode;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      super.writeExternal(out);
      out.writeFloat(this.no_entry_value);
      out.writeInt(this._size);
    int i = this._set.length;

      while (i-- > 0) {
         if (this._set[i] != REMOVED && this._set[i] != FREE) {
            out.writeObject(this._set[i]);
            out.writeFloat(this._values[i]);
         }
      }
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      super.readExternal(in);
      this.no_entry_value = in.readFloat();
    int size = in.readInt();
      this.setUp(size);

      while (size-- > 0) {
    K key = (K)in.readObject();
    float val = in.readFloat();
         this.put(key, val);
      }
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream("{");
      this.forEachEntry(std::make_shared<2>(this, buf));
      buf.append("}");
      return buf;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
