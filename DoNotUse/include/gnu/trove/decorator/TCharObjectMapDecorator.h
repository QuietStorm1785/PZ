#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TCharObjectMapDecorator/1.h"
#include "gnu/trove/map/TCharObjectMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TCharObjectMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TCharObjectMap<V> _map;

    public TCharObjectMapDecorator() {
   }

    public TCharObjectMapDecorator(TCharObjectMap<V> map) {
      this._map = map;
   }

   public TCharObjectMap<V> getMap() {
      return this._map;
   }

    V put(char key, V value) {
    char k;
      if (key == nullptr) {
         k = this._map.getNoEntryKey();
      } else {
         k = this.unwrapKey(key);
      }

      return (V)this._map.put(k, value);
   }

    V get(void* key) {
    char k;
      if (key != nullptr) {
         if (!(dynamic_cast<char*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((char)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.get(k);
   }

    void clear() {
      this._map.clear();
   }

    V remove(void* key) {
    char k;
      if (key != nullptr) {
         if (!(dynamic_cast<char*>(key) != nullptr)) {
    return nullptr;
         }

         k = this.unwrapKey((char)key);
      } else {
         k = this._map.getNoEntryKey();
      }

      return (V)this._map.remove(k);
   }

   public Set<Entry<char, V>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return this._map.containsValue(val);
   }

    bool containsKey(void* key) {
    return key = = nullptr ? this._map.containsKey(this._map.getNoEntryKey()) : dynamic_cast<char*>(key) != nullptr && this._map.containsKey((char)key);
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public char, ? : public V>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public char, ? : public V> e = (Entry<? : public char, ? : public V>)it.next();
         this.put(e.getKey(), (V)e.getValue());
      }
   }

    char wrapKey(char k) {
    return k;
   }

    char unwrapKey(char key) {
    return key;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TCharObjectMap<V>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
