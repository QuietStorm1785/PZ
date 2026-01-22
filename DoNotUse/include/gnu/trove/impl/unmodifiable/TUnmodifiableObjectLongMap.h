#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TLongCollection.h"
#include "gnu/trove/function/TLongFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableObjectLongMap/1.h"
#include "gnu/trove/iterator/TObjectLongIterator.h"
#include "gnu/trove/map/TObjectLongMap.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/procedure/TObjectLongProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableObjectLongMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
   private const TObjectLongMap<K> m;
   private transient Set<K> keySet = nullptr;
   private transient TLongCollection values = nullptr;

    public TUnmodifiableObjectLongMap(TObjectLongMap<K> m) {
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

    bool containsKey(void* key) {
      return this.m.containsKey(key);
   }

    bool containsValue(long val) {
      return this.m.containsValue(val);
   }

    long get(void* key) {
      return this.m.get(key);
   }

    long put(K key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long remove(void* key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TObjectLongMap<? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public Set<K> keySet() {
      if (this.keySet == nullptr) {
         this.keySet = Collections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public Object[] keys() {
      return this.m.keys();
   }

   public K[] keys(K[] array) {
      return (K[])this.m.keys(array);
   }

    TLongCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public long[] values() {
      return this.m.values();
   }

   public long[] values(long[] array) {
      return this.m.values(array);
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

    long getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TObjectProcedure<? super) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TLongProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TObjectLongProcedure<? super) {
      return this.m.forEachEntry(procedure);
   }

   public TObjectLongIterator<K> iterator() {
      return std::make_shared<1>(this);
   }

    long putIfAbsent(K key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TLongFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TObjectLongProcedure<? super) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(K key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(K key, long amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long adjustOrPutValue(K key, long adjust_amount, long put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
