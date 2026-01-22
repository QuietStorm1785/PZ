#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TDoubleIntMapDecorator/1.h"
#include "gnu/trove/map/TDoubleIntMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TDoubleIntMapDecorator : public AbstractMap {
public:
    static const long serialVersionUID = 1L;
    TDoubleIntMap _map;

    public TDoubleIntMapDecorator() {
   }

    public TDoubleIntMapDecorator(TDoubleIntMap map) {
      this._map = map;
   }

    TDoubleIntMap getMap() {
      return this._map;
   }

    int put(double key, int value) {
    double k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

    int v;
      if (value == nullptr) {
         v = this._map.getNoEntryValue();
      } else {
         v = this.unwrapValue(value);
      }

    int retval = this._map.put(k, v);
    return retval = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(retval);
   }

    int get(void* key) {
    double k;
      if (key != nullptr) {
         if (!(dynamic_cast<double*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    int v = this._map.get(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    int remove(void* key) {
    double k;
      if (key != nullptr) {
         if (!(dynamic_cast<double*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey(key);
      } else {
         k = this._map.getNoEntryKey();
      }

    int v = this._map.remove(k);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<double, int>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<int*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<double*>(key) != nullptr && this._map.containsKey(this.unwrapKey(key));
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public double, ? : public int>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public double, ? : public int> e = (Entry<? : public double, ? : public int>)it.next();
         this.put(e.getKey(), e.getValue());
      }
   }

    double wrapKey(double k) {
    return k;
   }

    double unwrapKey(void* key) {
      return (double)key;
   }

    int wrapValue(int k) {
    return k;
   }

    int unwrapValue(void* value) {
      return (int)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TDoubleIntMap)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
