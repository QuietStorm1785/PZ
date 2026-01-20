#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TLongShortMapDecorator/1.h"
#include "gnu/trove/map/TLongShortMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TLongShortMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TLongShortMap _map;

    public TLongShortMapDecorator() {
   }

    public TLongShortMapDecorator(TLongShortMap map) {
      this._map = map;
   }

    TLongShortMap getMap() {
      return this._map;
   }

    short put(long key, short value) {
    long k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

    short v;
      if (value == nullptr) {
         v = this._map.getNoEntryValue();
      } else {
         v = this.unwrapValue(value);
      }

    short retval = this._map.put(k, v);
    return retval = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(retval);
   }

    short get(void* key) {
    long k;
      if (key != nullptr) {
         if (!(dynamic_cast<int64_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    short v = this._map.get(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    short remove(void* key) {
    long k;
      if (key != nullptr) {
         if (!(dynamic_cast<int64_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    short v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<int64_t, int16_t>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<int16_t*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<int64_t*>(key) != nullptr && this._map.containsKey(this.unwrapKey(key));
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public int64_t, ? : public int16_t>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int64_t, ? : public int16_t> e = (Entry<? : public int64_t, ? : public int16_t>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    long wrapKey(long k) {
    return k;
   }

    long unwrapKey(void* key) {
      return (int64_t)key;
   }

    short wrapValue(short k) {
    return k;
   }

    short unwrapValue(void* value) {
      return (int16_t)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TLongShortMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
