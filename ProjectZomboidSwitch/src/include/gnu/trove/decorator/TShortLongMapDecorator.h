#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TShortLongMapDecorator/1.h"
#include "gnu/trove/map/TShortLongMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TShortLongMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TShortLongMap _map;

    public TShortLongMapDecorator() {
   }

    public TShortLongMapDecorator(TShortLongMap map) {
      this._map = map;
   }

    TShortLongMap getMap() {
      return this._map;
   }

    long put(short key, long value) {
    short k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

    long v;
      if (value == nullptr) {
         v = this._map.getNoEntryValue();
      } else {
         v = this.unwrapValue(value);
      }

    long retval = this._map.put(k, v);
    return retval = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(retval);
   }

    long get(void* key) {
    short k;
      if (key != nullptr) {
         if (!(dynamic_cast<int16_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    long v = this._map.get(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    long remove(void* key) {
    short k;
      if (key != nullptr) {
         if (!(dynamic_cast<int16_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    long v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<int16_t, int64_t>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<int64_t*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<int16_t*>(key) != nullptr && this._map.containsKey(this.unwrapKey(key));
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public int16_t, ? : public int64_t>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int16_t, ? : public int64_t> e = (Entry<? : public int16_t, ? : public int64_t>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    short wrapKey(short k) {
    return k;
   }

    short unwrapKey(void* key) {
      return (int16_t)key;
   }

    long wrapValue(long k) {
    return k;
   }

    long unwrapValue(void* value) {
      return (int64_t)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TShortLongMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
