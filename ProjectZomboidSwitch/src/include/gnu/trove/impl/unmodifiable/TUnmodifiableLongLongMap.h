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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongLongMap/1.h"
#include "gnu/trove/iterator/TLongLongIterator.h"
#include "gnu/trove/map/TLongLongMap.h"
#include "gnu/trove/procedure/TLongLongProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableLongLongMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TLongLongMap m;
   private transient TLongSet keySet = nullptr;
   private transient TLongCollection values = nullptr;

    public TUnmodifiableLongLongMap(TLongLongMap m) {
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

    bool containsValue(long val) {
      return this.m.containsValue(val);
   }

    long get(long key) {
      return this.m.get(key);
   }

    long put(long key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long remove(long key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TLongLongMap m) {
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

    long getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    long getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TLongProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TLongProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TLongLongProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TLongLongIterator iterator() {
      return std::make_shared<1>(this);
   }

    long putIfAbsent(long key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TLongFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TLongLongProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(long key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(long key, long amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long adjustOrPutValue(long key, long adjust_amount, long put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
