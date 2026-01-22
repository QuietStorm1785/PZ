#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongObjectMap/1.h"
#include "gnu/trove/iterator/TLongObjectIterator.h"
#include "gnu/trove/map/TLongObjectMap.h"
#include "gnu/trove/procedure/TLongObjectProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TLongSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableLongObjectMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TLongObjectMap<V> m;
   private transient TLongSet keySet = nullptr;
   private transient Collection<V> values = nullptr;

    public TUnmodifiableLongObjectMap(TLongObjectMap<V> m) {
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

    bool containsKey(long key) {
      return this.m.containsKey(key);
   }

    bool containsValue(void* val) {
      return this.m.containsValue(val);
   }

    V get(long key) {
      return (V)this.m.get(key);
   }

    V put(long key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(long key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TLongObjectMap<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TLongSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public long[] keys() {
      return this.m.keys();
   }

   public long[] keys(long[] array) {
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

    long getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    bool forEachKey(TLongProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TObjectProcedure<? super) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TLongObjectProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TLongObjectIterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    V putIfAbsent(long key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(V> function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TLongObjectProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
