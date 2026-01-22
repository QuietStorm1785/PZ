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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharFloatMap/1.h"
#include "gnu/trove/iterator/TCharFloatIterator.h"
#include "gnu/trove/map/TCharFloatMap.h"
#include "gnu/trove/procedure/TCharFloatProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TCharSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharFloatMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TCharFloatMap m;
   private transient TCharSet keySet = nullptr;
   private transient TFloatCollection values = nullptr;

    public TUnmodifiableCharFloatMap(TCharFloatMap m) {
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

    bool containsValue(float val) {
      return this.m.containsValue(val);
   }

    float get(char key) {
      return this.m.get(key);
   }

    float put(char key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float remove(char key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TCharFloatMap m) {
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

    char getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    float getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TCharProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TFloatProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TCharFloatProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TCharFloatIterator iterator() {
      return std::make_shared<1>(this);
   }

    float putIfAbsent(char key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TFloatFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TCharFloatProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(char key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(char key, float amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float adjustOrPutValue(char key, float adjust_amount, float put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
