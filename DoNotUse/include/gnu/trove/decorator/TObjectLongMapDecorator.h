#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectLongMapDecorator/1.h"
#include "gnu/trove/map/TObjectLongMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectLongMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TObjectLongMap<K> _map;

    public TObjectLongMapDecorator() {
   }

    public TObjectLongMapDecorator(TObjectLongMap<K> map) {
      this._map = map;
   }

   public TObjectLongMap<K> getMap() {
      return this._map;
   }

    long put(K key, long value) {
    return value = = nullptr ? this.wrapValue(this._map.put(key, this._map.getNoEntryValue())) : this.wrapValue(this._map.put(key, this.unwrapValue(value)));
   }

    long get(void* key) {
    long v = this._map.get(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    long remove(void* key) {
    long v = this._map.remove(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<K, int64_t>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<int64_t*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public K, ? : public int64_t>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public K, ? : public int64_t> e = (Entry<? : public K, ? : public int64_t>)it.next();
         this.put((K)e.getKey(), e.getValue());
      }
   }

    long wrapValue(long k) {
    return k;
   }

    long unwrapValue(void* value) {
      return (int64_t)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TObjectLongMap<K>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
