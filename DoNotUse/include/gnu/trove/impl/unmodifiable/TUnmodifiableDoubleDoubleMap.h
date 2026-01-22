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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleDoubleMap/1.h"
#include "gnu/trove/iterator/TDoubleDoubleIterator.h"
#include "gnu/trove/map/TDoubleDoubleMap.h"
#include "gnu/trove/procedure/TDoubleDoubleProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableDoubleDoubleMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TDoubleDoubleMap m;
   private transient TDoubleSet keySet = nullptr;
   private transient TDoubleCollection values = nullptr;

    public TUnmodifiableDoubleDoubleMap(TDoubleDoubleMap m) {
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

    bool containsKey(double key) {
      return this.m.containsKey(key);
   }

    bool containsValue(double val) {
      return this.m.containsValue(val);
   }

    double get(double key) {
      return this.m.get(key);
   }

    double put(double key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double remove(double key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TDoubleDoubleMap m) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TDoubleSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public double[] keys() {
      return this.m.keys();
   }

   public double[] keys(double[] array) {
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

    double getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    double getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TDoubleProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TDoubleProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TDoubleDoubleProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TDoubleDoubleIterator iterator() {
      return std::make_shared<1>(this);
   }

    double putIfAbsent(double key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TDoubleFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TDoubleDoubleProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(double key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(double key, double amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double adjustOrPutValue(double key, double adjust_amount, double put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
