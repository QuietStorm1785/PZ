#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntObjectMap/1.h"
#include "gnu/trove/iterator/TIntObjectIterator.h"
#include "gnu/trove/map/TIntObjectMap.h"
#include "gnu/trove/procedure/TIntObjectProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntObjectMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TIntObjectMap<V> m;
   private transient TIntSet keySet = nullptr;
   private transient Collection<V> values = nullptr;

    public TUnmodifiableIntObjectMap(TIntObjectMap<V> m) {
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

    bool containsKey(int key) {
      return this.m.containsKey(key);
   }

    bool containsValue(void* val) {
      return this.m.containsValue(val);
   }

    V get(int key) {
      return (V)this.m.get(key);
   }

    V put(int key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TIntObjectMap<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TIntSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public int[] keys() {
      return this.m.keys();
   }

   public int[] keys(int[] array) {
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

    int getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    bool forEachKey(TIntProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TObjectProcedure<? super) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TIntObjectProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TIntObjectIterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    V putIfAbsent(int key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(V> function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TIntObjectProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
