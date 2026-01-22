#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectFloatMapDecorator/1.h"
#include "gnu/trove/map/TObjectFloatMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectFloatMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TObjectFloatMap<K> _map;

    public TObjectFloatMapDecorator() {
   }

    public TObjectFloatMapDecorator(TObjectFloatMap<K> map) {
      this._map = map;
   }

   public TObjectFloatMap<K> getMap() {
      return this._map;
   }

    float put(K key, float value) {
    return value = = nullptr ? this.wrapValue(this._map.put(key, this._map.getNoEntryValue())) : this.wrapValue(this._map.put(key, this.unwrapValue(value)));
   }

    float get(void* key) {
    float v = this._map.get(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    float remove(void* key) {
    float v = this._map.remove(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<K, float>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<float*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public K, ? : public float>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public K, ? : public float> e = (Entry<? : public K, ? : public float>)it.next();
         this.put((K)e.getKey(), e.getValue());
      }
   }

    float wrapValue(float k) {
    return k;
   }

    float unwrapValue(void* value) {
      return (float)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TObjectFloatMap<K>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
