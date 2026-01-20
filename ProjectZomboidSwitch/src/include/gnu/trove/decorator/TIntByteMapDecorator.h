#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TIntByteMapDecorator/1.h"
#include "gnu/trove/map/TIntByteMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TIntByteMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TIntByteMap _map;

    public TIntByteMapDecorator() {
   }

    public TIntByteMapDecorator(TIntByteMap map) {
      this._map = map;
   }

    TIntByteMap getMap() {
      return this._map;
   }

    uint8_t put(int key, uint8_t value) {
    int k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

    uint8_t v;
      if (value == nullptr) {
         v = this._map.getNoEntryValue();
      } else {
         v = this.unwrapValue(value);
      }

    uint8_t retval = this._map.put(k, v);
    return retval = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(retval);
   }

    uint8_t get(void* key) {
    int k;
      if (key != nullptr) {
         if (!(dynamic_cast<int*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    uint8_t v = this._map.get(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    uint8_t remove(void* key) {
    int k;
      if (key != nullptr) {
         if (!(dynamic_cast<int*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    uint8_t v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<int, uint8_t>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<uint8_t*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public int, ? : public uint8_t>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int, ? : public uint8_t> e = (Entry<? : public int, ? : public uint8_t>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    int wrapKey(int k) {
    return k;
   }

    int unwrapKey(void* key) {
      return (int)key;
   }

    uint8_t wrapValue(uint8_t k) {
    return k;
   }

    uint8_t unwrapValue(void* value) {
      return (uint8_t)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TIntByteMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
