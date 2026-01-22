#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TLongObjectMapDecorator/1.h"
#include "gnu/trove/map/TLongObjectMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TLongObjectMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TLongObjectMap<V> _map;

    public TLongObjectMapDecorator() {
   }

    public TLongObjectMapDecorator(TLongObjectMap<V> map) {
      this._map = map;
   }

   public TLongObjectMap<V> getMap() {
      return this._map;
   }

    V put(long key, V value) {
    long k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

      return (V)this._map.put(k, value);
   }

    V get(void* key) {
    long k;
      if (key != nullptr) {
         if (!(dynamic_cast<int64_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((int64_t)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.get(k);
   }

    void clear() {
      this._map.clear();
   }

    V remove(void* key) {
    long k;
      if (key != nullptr) {
         if (!(dynamic_cast<int64_t*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((int64_t)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.remove(k);
   }

   public Set<Entry<int64_t, V>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return this._map.containsValue(val);
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<int64_t*>(key) != nullptr && this._map.containsKey((int64_t)key);
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public int64_t, ? : public V>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int64_t, ? : public V> e = (Entry<? : public int64_t, ? : public V>)it.next();
         this.put(e.getKey(), (V)e.getValue());
      }
   }

    long wrapKey(long k) {
    return k;
   }

    long unwrapKey(long key) {
    return key;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TLongObjectMap<V>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
