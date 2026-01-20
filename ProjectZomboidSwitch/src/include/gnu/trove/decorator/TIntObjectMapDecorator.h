#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TIntObjectMapDecorator/1.h"
#include "gnu/trove/map/TIntObjectMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TIntObjectMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TIntObjectMap<V> _map;

    public TIntObjectMapDecorator() {
   }

    public TIntObjectMapDecorator(TIntObjectMap<V> map) {
      this._map = map;
   }

   public TIntObjectMap<V> getMap() {
      return this._map;
   }

    V put(int key, V value) {
    int k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

      return (V)this._map.put(k, value);
   }

    V get(void* key) {
    int k;
      if (key != nullptr) {
         if (!(dynamic_cast<int*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((int)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.get(k);
   }

    void clear() {
      this._map.clear();
   }

    V remove(void* key) {
    int k;
      if (key != nullptr) {
         if (!(dynamic_cast<int*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((int)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.remove(k);
   }

   public Set<Entry<int, V>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return this._map.containsValue(val);
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<int*>(key) != nullptr && this._map.containsKey((int)key);
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public int, ? : public V>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public int, ? : public V> e = (Entry<? : public int, ? : public V>)it.next();
         this.put(e.getKey(), (V)e.getValue());
      }
   }

    int wrapKey(int k) {
    return k;
   }

    int unwrapKey(int key) {
    return key;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TIntObjectMap<V>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
