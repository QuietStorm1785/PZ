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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatDoubleMap/1.h"
#include "gnu/trove/iterator/TFloatDoubleIterator.h"
#include "gnu/trove/map/TFloatDoubleMap.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TFloatDoubleProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatDoubleMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TFloatDoubleMap m;
   private transient TFloatSet keySet = nullptr;
   private transient TDoubleCollection values = nullptr;

    public TUnmodifiableFloatDoubleMap(TFloatDoubleMap m) {
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

    bool containsValue(double val) {
      return this.m.containsValue(val);
   }

    double get(float key) {
      return this.m.get(key);
   }

    double put(float key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double remove(float key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TFloatDoubleMap m) {
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

    float getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    double getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TFloatProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TDoubleProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TFloatDoubleProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TFloatDoubleIterator iterator() {
      return std::make_shared<1>(this);
   }

    double putIfAbsent(float key, double value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TDoubleFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TFloatDoubleProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(float key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(float key, double amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    double adjustOrPutValue(float key, double adjust_amount, double put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
