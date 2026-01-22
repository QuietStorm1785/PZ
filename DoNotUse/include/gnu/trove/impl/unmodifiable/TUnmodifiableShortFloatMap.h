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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableShortFloatMap/1.h"
#include "gnu/trove/iterator/TShortFloatIterator.h"
#include "gnu/trove/map/TShortFloatMap.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TShortFloatProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TShortSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableShortFloatMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TShortFloatMap m;
   private transient TShortSet keySet = nullptr;
   private transient TFloatCollection values = nullptr;

    public TUnmodifiableShortFloatMap(TShortFloatMap m) {
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

    bool containsValue(float val) {
      return this.m.containsValue(val);
   }

    float get(short key) {
      return this.m.get(key);
   }

    float put(short key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float remove(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TShortFloatMap m) {
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

    short getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    float getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TShortProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TFloatProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TShortFloatProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TShortFloatIterator iterator() {
      return std::make_shared<1>(this);
   }

    float putIfAbsent(short key, float value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TFloatFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TShortFloatProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(short key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(short key, float amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    float adjustOrPutValue(short key, float adjust_amount, float put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
