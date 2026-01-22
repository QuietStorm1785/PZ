#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TByteObjectMapDecorator/1.h"
#include "gnu/trove/map/TByteObjectMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TByteObjectMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TByteObjectMap<V> _map;

    public TByteObjectMapDecorator() {
   }

    public TByteObjectMapDecorator(TByteObjectMap<V> map) {
      this._map = map;
   }

   public TByteObjectMap<V> getMap() {
      return this._map;
   }

    V put(uint8_t key, V value) {
    uint8_t k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

      return (V)this._map.put(k, value);
   }

    V get(void* key) {
    uint8_t k;
      if (key != nullptr) {
         if (!(dynamic_cast<uint8_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((uint8_t)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.get(k);
   }

    void clear() {
      this._map.clear();
   }

    V remove(void* key) {
    uint8_t k;
      if (key != nullptr) {
         if (!(dynamic_cast<uint8_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((uint8_t)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.remove(k);
   }

   public Set<Entry<uint8_t, V>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return this._map.containsValue(val);
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<uint8_t*>(key) != nullptr && this._map.containsKey((uint8_t)key);
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public uint8_t, ? : public V>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public uint8_t, ? : public V> e = (Entry<? : public uint8_t, ? : public V>)it.next();
         this.put(e.getKey(), (V)e.getValue());
      }
   }

    uint8_t wrapKey(uint8_t k) {
    return k;
   }

    uint8_t unwrapKey(uint8_t key) {
    return key;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TByteObjectMap<V>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
