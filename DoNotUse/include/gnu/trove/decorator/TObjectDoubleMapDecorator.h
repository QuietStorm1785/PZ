#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/decorator/TObjectDoubleMapDecorator/1.h"
#include "gnu/trove/map/TObjectDoubleMap.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace gnu {
namespace trove {
namespace decorator {


class TObjectDoubleMapDecorator {
public:
    static const long serialVersionUID = 1L;
   protected TObjectDoubleMap<K> _map;

    public TObjectDoubleMapDecorator() {
   }

    public TObjectDoubleMapDecorator(TObjectDoubleMap<K> map) {
      this._map = map;
   }

   public TObjectDoubleMap<K> getMap() {
      return this._map;
   }

    double put(K key, double value) {
    return value = = nullptr ? this.wrapValue(this._map.put(key, this._map.getNoEntryValue())) : this.wrapValue(this._map.put(key, this.unwrapValue(value)));
   }

    double get(void* key) {
    double v = this._map.get(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

    void clear() {
      this._map.clear();
   }

    double remove(void* key) {
    double v = this._map.remove(key);
    return v = = this._map.getNoEntryValue() ? nullptr : this.wrapValue(v);
   }

   public Set<Entry<K, double>> entrySet() {
      return std::make_shared<1>(this);
   }

    bool containsValue(void* val) {
      return dynamic_cast<double*>(val) != nullptr && this._map.containsValue(this.unwrapValue(val));
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
      Iterator<? : public Entry<? : public K, ? : public double>> it = map.entrySet().iterator();
    int i = map.size();

      while (i-- > 0) {
         Entry<? : public K, ? : public double> e = (Entry<? : public K, ? : public double>)it.next();
         this.put((K)e.getKey(), e.getValue());
      }
   }

    double wrapValue(double k) {
    return k;
   }

    double unwrapValue(void* value) {
      return (double)value;
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._map = (TObjectDoubleMap<K>)in.readObject();
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeObject(this._map);
   }
}
} // namespace decorator
} // namespace trove
} // namespace gnu
