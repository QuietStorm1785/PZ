#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleFloatMap/1.h"
#include "gnu/trove/iterator/TDoubleFloatIterator.h"
#include "gnu/trove/map/TDoubleFloatMap.h"
#include "gnu/trove/procedure/TDoubleFloatProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableDoubleFloatMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TDoubleFloatMap m;
   private transient TDoubleSet keySet = nullptr;
   private transient TFloatCollection values = nullptr;

    public TUnmodifiableDoubleFloatMap(TDoubleFloatMap m) {
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

    bool containsValue(float val) {
      return this.m.containsValue(val);
   }

    float get(double key) {
      return this.m.get(key);
   }

    float put(double key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float remove(double key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TDoubleFloatMap m) {
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

    TFloatCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public float[] values() {
      return this.m.values();
   }

   public float[] values(float[] array) {
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

    float getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TDoubleProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TFloatProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TDoubleFloatProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TDoubleFloatIterator iterator() {
      return std::make_shared<1>(this);
   }

    float putIfAbsent(double key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TFloatFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TDoubleFloatProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(double key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(double key, float amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float adjustOrPutValue(double key, float adjust_amount, float put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
