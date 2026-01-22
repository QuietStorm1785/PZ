#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TShortDoubleMapDecorator/1.h"
#include "gnu/trove/map/TShortDoubleMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TShortDoubleMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TShortDoubleMap _map;

    public TShortDoubleMapDecorator() {
   }

    public TShortDoubleMapDecorator(TShortDoubleMap map) {
      this._map = map;
   }

    TShortDoubleMap getMap() {
      return this._map;
   }

    double put(short key, double value) {
    short k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

    double v;
      if (value == nullptr) {
         v = this._map.getNoEntryValue();
      } else {
         v = this.unwrapValue(value);
      }

    double retval = this._map.put(k, v);
    return retval = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(retval);
   }

    double get(void* key) {
    short k;
      if (key != nullptr) {
         if (!(dynamic_cast<int16_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    double v = this._map.get(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    double remove(void* key) {
    short k;
      if (key != nullptr) {
         if (!(dynamic_cast<int16_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    double v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<int16_t, double>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<double*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public int16_t, ? : public double>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int16_t, ? : public double> e = (Entry<? : public int16_t, ? : public double>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    short wrapKey(short k) {
    return k;
   }

    short unwrapKey(void* key) {
      return (int16_t)key;
   }

    double wrapValue(double k) {
    return k;
   }

    double unwrapValue(void* value) {
      return (double)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TShortDoubleMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
