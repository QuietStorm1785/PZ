#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TFloatCharMapDecorator/1.h"
#include "gnu/trove/map/TFloatCharMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TFloatCharMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TFloatCharMap _map;

    public TFloatCharMapDecorator() {
   }

    public TFloatCharMapDecorator(TFloatCharMap map) {
      this._map = map;
   }

    TFloatCharMap getMap() {
      return this._map;
   }

    char put(float key, char value) {
    float k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

    char v;
      if (value == nullptr) {
         v = this._map.getNoEntryValue();
      } else {
         v = this.unwrapValue(value);
      }

    char retval = this._map.put(k, v);
    return retval = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(retval);
   }

    char get(void* key) {
    float k;
      if (key != nullptr) {
         if (!(dynamic_cast<float*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    char v = this._map.get(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    char remove(void* key) {
    float k;
      if (key != nullptr) {
         if (!(dynamic_cast<float*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    char v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<float, char>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<char*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<float*>(key) != nullptr && this._map.containsKey(this.unwrapKey(key));
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public float, ? : public char>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public float, ? : public char> e = (Entry<? : public float, ? : public char>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    float wrapKey(float k) {
    return k;
   }

    float unwrapKey(void* key) {
      return (float)key;
   }

    char wrapValue(char k) {
    return k;
   }

    char unwrapValue(void* value) {
      return (char)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TFloatCharMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
