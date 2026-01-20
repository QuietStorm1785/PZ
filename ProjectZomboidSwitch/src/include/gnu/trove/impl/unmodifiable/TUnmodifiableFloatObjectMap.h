#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatObjectMap/1.h"
#include "gnu/trove/iterator/TFloatObjectIterator.h"
#include "gnu/trove/map/TFloatObjectMap.h"
#include "gnu/trove/procedure/TFloatObjectProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TFloatSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatObjectMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TFloatObjectMap<V> m;
   private transient TFloatSet keySet = nullptr;
   private transient Collection<V> values = nullptr;

    public TUnmodifiableFloatObjectMap(TFloatObjectMap<V> m) {
      if (m == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         this.m = m;
      }
   }

    int size() {
      return this.m.size();
   }

    bool isEmpty() {
      return this.m.empty();
   }

    bool containsKey(float key) {
      return this.m.containsKey(key);
   }

    bool containsValue(void* val) {
      return this.m.containsValue(val);
   }

    V get(float key) {
      return (V)this.m.get(key);
   }

    V put(float key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(float key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TFloatObjectMap<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TFloatSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public float[] keys() {
      return this.m.keys();
   }

   public float[] keys(float[] array) {
      return this.m.keys(array);
   }

   public Collection<V> valueCollection() {
      if (this.values == nullptr) {
         this.values = Collections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public Object[] values() {
      return this.m.values();
   }

   public V[] values(V[] array) {
      return (V[])this.m.values(array);
   }

    bool equals(void* o) {
    return o = = this || this.m == o);
   }

    int hashCode() {
      return this.m.hashCode();
   }

    std::string toString() {
      return this.m;
   }

    float getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    bool forEachKey(TFloatProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TObjectProcedure<? super) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TFloatObjectProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TFloatObjectIterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    V putIfAbsent(float key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(V> function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TFloatObjectProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
