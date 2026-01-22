#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TIntShortMapDecorator/1.h"
#include "gnu/trove/map/TIntShortMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TIntShortMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TIntShortMap _map;

    public TIntShortMapDecorator() {
   }

    public TIntShortMapDecorator(TIntShortMap map) {
      this._map = map;
   }

    TIntShortMap getMap() {
      return this._map;
   }

    short put(int key, short value) {
    int k;
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
    int k;
      if (key != nullptr) {
         if (!(dynamic_cast<int*>(key) != nullptr)) {
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
    int k;
      if (key != nullptr) {
         if (!(dynamic_cast<int*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    short v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<int, int16_t>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<int16_t*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<int*>(key) != nullptr && this._map.containsKey(this.unwrapKey(key));
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public int, ? : public int16_t>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int, ? : public int16_t> e = (Entry<? : public int, ? : public int16_t>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    int wrapKey(int k) {
    return k;
   }

    int unwrapKey(void* key) {
      return (int)key;
   }

    short wrapValue(short k) {
    return k;
   }

    short unwrapValue(void* value) {
      return (int16_t)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TIntShortMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
