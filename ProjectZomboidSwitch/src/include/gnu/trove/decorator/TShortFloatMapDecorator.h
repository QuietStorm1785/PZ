#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TShortFloatMapDecorator/1.h"
#include "gnu/trove/map/TShortFloatMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TShortFloatMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TShortFloatMap _map;

    public TShortFloatMapDecorator() {
   }

    public TShortFloatMapDecorator(TShortFloatMap map) {
      this._map = map;
   }

    TShortFloatMap getMap() {
      return this._map;
   }

    float put(short key, float value) {
    short k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

    float v;
      if (value == nullptr) {
         v = this._map.getNoEntryValue();
      } else {
         v = this.unwrapValue(value);
      }

    float retval = this._map.put(k, v);
    return retval = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(retval);
   }

    float get(void* key) {
    short k;
      if (key != nullptr) {
         if (!(dynamic_cast<int16_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    float v = this._map.get(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    float remove(void* key) {
    short k;
      if (key != nullptr) {
         if (!(dynamic_cast<int16_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    float v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<int16_t, float>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<float*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public int16_t, ? : public float>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int16_t, ? : public float> e = (Entry<? : public int16_t, ? : public float>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    short wrapKey(short k) {
    return k;
   }

    short unwrapKey(void* key) {
      return (int16_t)key;
   }

    float wrapValue(float k) {
    return k;
   }

    float unwrapValue(void* value) {
      return (float)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TShortFloatMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
