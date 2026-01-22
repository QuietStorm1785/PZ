#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectShortMapDecorator/1.h"
#include "gnu/trove/map/TObjectShortMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectShortMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TObjectShortMap<K> _map;

    public TObjectShortMapDecorator() {
   }

    public TObjectShortMapDecorator(TObjectShortMap<K> map) {
      this._map = map;
   }

   public TObjectShortMap<K> getMap() {
      return this._map;
   }

    short put(K key, short value) {
    return value = = nullptr ? this.wrapValue(this._map.put(key, this._map.getNoEntryValue())) : this.wrapValue(this._map.put(key, this.unwrapValue(value)));
   }

    short get(void* key) {
    short v = this._map.get(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    short remove(void* key) {
    short v = this._map.remove(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<K, int16_t>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<int16_t*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public K, ? : public int16_t>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public K, ? : public int16_t> e = (Entry<? : public K, ? : public int16_t>)it.next();
         this.put((K)e.getKey(), e.getValue());
      }
   }

    short wrapValue(short k) {
    return k;
   }

    short unwrapValue(void* value) {
      return (int16_t)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TObjectShortMap<K>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
