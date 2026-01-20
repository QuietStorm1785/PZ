#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableDoubleShortMap/1.h"
#include "gnu/trove/iterator/TDoubleShortIterator.h"
#include "gnu/trove/map/TDoubleShortMap.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TDoubleShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableDoubleShortMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TDoubleShortMap m;
   private transient TDoubleSet keySet = nullptr;
   private transient TShortCollection values = nullptr;

    public TUnmodifiableDoubleShortMap(TDoubleShortMap m) {
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

    bool containsValue(short val) {
      return this.m.containsValue(val);
   }

    short get(double key) {
      return this.m.get(key);
   }

    short put(double key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short remove(double key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TDoubleShortMap m) {
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

    TShortCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public short[] values() {
      return this.m.values();
   }

   public short[] values(short[] array) {
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

    short getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TDoubleProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TShortProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TDoubleShortProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TDoubleShortIterator iterator() {
      return std::make_shared<1>(this);
   }

    short putIfAbsent(double key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TShortFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TDoubleShortProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(double key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(double key, short amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short adjustOrPutValue(double key, short adjust_amount, short put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
