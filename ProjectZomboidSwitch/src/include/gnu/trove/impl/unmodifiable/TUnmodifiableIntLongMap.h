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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntLongMap/1.h"
#include "gnu/trove/iterator/TIntLongIterator.h"
#include "gnu/trove/map/TIntLongMap.h"
#include "gnu/trove/procedure/TIntLongProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntLongMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TIntLongMap m;
   private transient TIntSet keySet = nullptr;
   private transient TLongCollection values = nullptr;

    public TUnmodifiableIntLongMap(TIntLongMap m) {
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

    bool containsValue(long val) {
      return this.m.containsValue(val);
   }

    long get(int key) {
      return this.m.get(key);
   }

    long put(int key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long remove(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TIntLongMap m) {
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

    int getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    long getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TIntProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TLongProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TIntLongProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TIntLongIterator iterator() {
      return std::make_shared<1>(this);
   }

    long putIfAbsent(int key, long value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TLongFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TIntLongProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(int key, long amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long adjustOrPutValue(int key, long adjust_amount, long put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
