#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectByteMapDecorator/1.h"
#include "gnu/trove/map/TObjectByteMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectByteMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TObjectByteMap<K> _map;

    public TObjectByteMapDecorator() {
   }

    public TObjectByteMapDecorator(TObjectByteMap<K> map) {
      this._map = map;
   }

   public TObjectByteMap<K> getMap() {
      return this._map;
   }

    uint8_t put(K key, uint8_t value) {
    return value = = nullptr ? this.wrapValue(this._map.put(key, this._map.getNoEntryValue())) : this.wrapValue(this._map.put(key, this.unwrapValue(value)));
   }

    uint8_t get(void* key) {
    uint8_t v = this._map.get(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    uint8_t remove(void* key) {
    uint8_t v = this._map.remove(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<K, uint8_t>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<uint8_t*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public K, ? : public uint8_t>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public K, ? : public uint8_t> e = (Entry<? : public K, ? : public uint8_t>)it.next();
         this.put((K)e.getKey(), e.getValue());
      }
   }

    uint8_t wrapValue(uint8_t k) {
    return k;
   }

    uint8_t unwrapValue(void* value) {
      return (uint8_t)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TObjectByteMap<K>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
