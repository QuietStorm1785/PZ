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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortDoubleMap/1.h"
#include "gnu/trove/iterator/TShortDoubleIterator.h"
#include "gnu/trove/map/TShortDoubleMap.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TShortDoubleProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortDoubleMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TShortDoubleMap m;
   private transient TShortSet keySet = nullptr;
   private transient TDoubleCollection values = nullptr;

    public TUnmodifiableShortDoubleMap(TShortDoubleMap m) {
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

    bool containsKey(short key) {
      return this.m.containsKey(key);
   }

    bool containsValue(double val) {
      return this.m.containsValue(val);
   }

    double get(short key) {
      return this.m.get(key);
   }

    double put(short key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double remove(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TShortDoubleMap m) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TShortSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public short[] keys() {
      return this.m.keys();
   }

   public short[] keys(short[] array) {
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

    short getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    double getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TShortProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TDoubleProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TShortDoubleProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TShortDoubleIterator iterator() {
      return std::make_shared<1>(this);
   }

    double putIfAbsent(short key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TDoubleFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TShortDoubleProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(short key, double amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double adjustOrPutValue(short key, double adjust_amount, double put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
