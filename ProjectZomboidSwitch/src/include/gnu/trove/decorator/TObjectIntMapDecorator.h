#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectIntMapDecorator/1.h"
#include "gnu/trove/map/TObjectIntMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectIntMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TObjectIntMap<K> _map;

    public TObjectIntMapDecorator() {
   }

    public TObjectIntMapDecorator(TObjectIntMap<K> map) {
      this._map = map;
   }

   public TObjectIntMap<K> getMap() {
      return this._map;
   }

    int put(K key, int value) {
    return value = = nullptr ? this.wrapValue(this._map.put(key, this._map.getNoEntryValue())) : this.wrapValue(this._map.put(key, this.unwrapValue(value)));
   }

    int get(void* key) {
    int v = this._map.get(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    int remove(void* key) {
    int v = this._map.remove(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<K, int>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<int*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public K, ? : public int>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public K, ? : public int> e = (Entry<? : public K, ? : public int>)it.next();
         this.put((K)e.getKey(), e.getValue());
      }
   }

    int wrapValue(int k) {
    return k;
   }

    int unwrapValue(void* value) {
      return (int)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TObjectIntMap<K>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
