#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TFloatObjectMapDecorator/1.h"
#include "gnu/trove/map/TFloatObjectMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TFloatObjectMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TFloatObjectMap<V> _map;

    public TFloatObjectMapDecorator() {
   }

    public TFloatObjectMapDecorator(TFloatObjectMap<V> map) {
      this._map = map;
   }

   public TFloatObjectMap<V> getMap() {
      return this._map;
   }

    V put(float key, V value) {
    float k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

      return (V)this._map.put(k, value);
   }

    V get(void* key) {
    float k;
      if (key != nullptr) {
         if (!(dynamic_cast<float*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((float)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.get(k);
   }

    void clear() {
      this._map.clear();
   }

    V remove(void* key) {
    float k;
      if (key != nullptr) {
         if (!(dynamic_cast<float*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((float)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.remove(k);
   }

   public Set<Entry<float, V>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return this._map.containsValue(val);
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<float*>(key) != nullptr && this._map.containsKey((float)key);
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public float, ? : public V>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public float, ? : public V> e = (Entry<? : public float, ? : public V>)it.next();
         this.put(e.getKey(), (V)e.getValue());
      }
   }

    float wrapKey(float k) {
    return k;
   }

    float unwrapKey(float key) {
    return key;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TFloatObjectMap<V>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
