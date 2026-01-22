#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TDoubleObjectMapDecorator/1.h"
#include "gnu/trove/map/TDoubleObjectMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TDoubleObjectMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TDoubleObjectMap<V> _map;

    public TDoubleObjectMapDecorator() {
   }

    public TDoubleObjectMapDecorator(TDoubleObjectMap<V> map) {
      this._map = map;
   }

   public TDoubleObjectMap<V> getMap() {
      return this._map;
   }

    V put(double key, V value) {
    double k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

      return (V)this._map.put(k, value);
   }

    V get(void* key) {
    double k;
      if (key != nullptr) {
         if (!(dynamic_cast<double*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((double)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.get(k);
   }

    void clear() {
      this._map.clear();
   }

    V remove(void* key) {
    double k;
      if (key != nullptr) {
         if (!(dynamic_cast<double*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((double)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.remove(k);
   }

   public Set<Entry<double, V>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return this._map.containsValue(val);
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<double*>(key) != nullptr && this._map.containsKey((double)key);
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public double, ? : public V>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public double, ? : public V> e = (Entry<? : public double, ? : public V>)it.next();
         this.put(e.getKey(), (V)e.getValue());
      }
   }

    double wrapKey(double k) {
    return k;
   }

    double unwrapKey(double key) {
    return key;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TDoubleObjectMap<V>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
