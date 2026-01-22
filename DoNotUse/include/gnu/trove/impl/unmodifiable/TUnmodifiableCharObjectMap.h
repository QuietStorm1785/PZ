#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharObjectMap/1.h"
#include "gnu/trove/iterator/TCharObjectIterator.h"
#include "gnu/trove/map/TCharObjectMap.h"
#include "gnu/trove/procedure/TCharObjectProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TCharSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharObjectMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TCharObjectMap<V> m;
   private transient TCharSet keySet = nullptr;
   private transient Collection<V> values = nullptr;

    public TUnmodifiableCharObjectMap(TCharObjectMap<V> m) {
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

    bool containsKey(char key) {
      return this.m.containsKey(key);
   }

    bool containsValue(void* val) {
      return this.m.containsValue(val);
   }

    V get(char key) {
      return (V)this.m.get(key);
   }

    V put(char key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    V remove(char key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TCharObjectMap<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TCharSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public char[] keys() {
      return this.m.keys();
   }

   public char[] keys(char[] array) {
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

    char getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    bool forEachKey(TCharProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TObjectProcedure<? super) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TCharObjectProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TCharObjectIterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    V putIfAbsent(char key, V value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(V> function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TCharObjectProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
