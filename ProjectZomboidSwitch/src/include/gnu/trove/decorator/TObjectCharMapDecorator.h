#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectCharMapDecorator/1.h"
#include "gnu/trove/map/TObjectCharMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectCharMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TObjectCharMap<K> _map;

    public TObjectCharMapDecorator() {
   }

    public TObjectCharMapDecorator(TObjectCharMap<K> map) {
      this._map = map;
   }

   public TObjectCharMap<K> getMap() {
      return this._map;
   }

    char put(K key, char value) {
    return value = = nullptr ? this.wrapValue(this._map.put(key, this._map.getNoEntryValue())) : this.wrapValue(this._map.put(key, this.unwrapValue(value)));
   }

    char get(void* key) {
    char v = this._map.get(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    char remove(void* key) {
    char v = this._map.remove(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<K, char>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<char*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
   }

    bool containsKey(void* key) {
      return this._map.containsKey(key);
   }

    int size() {
      return this._map.size();
   }

    bool isEmpty() {
      return this._map.size() == 0;
   }

    void putAll(Map<? extends, ? extends) {
      Iterator<? : public Entry<? : public K, ? : public char>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public K, ? : public char> e = (Entry<? : public K, ? : public char>)it.next();
         this.put((K)e.getKey(), e.getValue());
      }
   }

    char wrapValue(char k) {
    return k;
   }

    char unwrapValue(void* value) {
      return (char)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TObjectCharMap<K>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
