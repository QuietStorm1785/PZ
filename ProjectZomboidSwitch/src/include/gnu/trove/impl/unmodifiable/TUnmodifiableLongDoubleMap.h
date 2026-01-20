#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableLongDoubleMap/1.h"
#include "gnu/trove/iterator/TLongDoubleIterator.h"
#include "gnu/trove/map/TLongDoubleMap.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TLongDoubleProcedure.h"
#include "gnu/trove/procedure/TLongProcedure.h"
#include "gnu/trove/set/TLongSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableLongDoubleMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TLongDoubleMap m;
   private transient TLongSet keySet = nullptr;
   private transient TDoubleCollection values = nullptr;

    public TUnmodifiableLongDoubleMap(TLongDoubleMap m) {
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

    bool containsValue(double val) {
      return this.m.containsValue(val);
   }

    double get(long key) {
      return this.m.get(key);
   }

    double put(long key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double remove(long key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TLongDoubleMap m) {
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

    TDoubleCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public double[] values() {
      return this.m.values();
   }

   public double[] values(double[] array) {
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

    double getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TLongProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TDoubleProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TLongDoubleProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TLongDoubleIterator iterator() {
      return std::make_shared<1>(this);
   }

    double putIfAbsent(long key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TDoubleFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TLongDoubleProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(long key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(long key, double amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double adjustOrPutValue(long key, double adjust_amount, double put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
