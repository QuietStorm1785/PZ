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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatFloatMap/1.h"
#include "gnu/trove/iterator/TFloatFloatIterator.h"
#include "gnu/trove/map/TFloatFloatMap.h"
#include "gnu/trove/procedure/TFloatFloatProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatFloatMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TFloatFloatMap m;
   private transient TFloatSet keySet = nullptr;
   private transient TFloatCollection values = nullptr;

    public TUnmodifiableFloatFloatMap(TFloatFloatMap m) {
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

    bool containsValue(float val) {
      return this.m.containsValue(val);
   }

    float get(float key) {
      return this.m.get(key);
   }

    float put(float key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float remove(float key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TFloatFloatMap m) {
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

    float getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    float getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TFloatProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TFloatProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TFloatFloatProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TFloatFloatIterator iterator() {
      return std::make_shared<1>(this);
   }

    float putIfAbsent(float key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TFloatFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TFloatFloatProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(float key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(float key, float amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float adjustOrPutValue(float key, float adjust_amount, float put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
