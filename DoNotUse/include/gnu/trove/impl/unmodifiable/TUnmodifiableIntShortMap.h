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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntShortMap/1.h"
#include "gnu/trove/iterator/TIntShortIterator.h"
#include "gnu/trove/map/TIntShortMap.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TIntShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntShortMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TIntShortMap m;
   private transient TIntSet keySet = nullptr;
   private transient TShortCollection values = nullptr;

    public TUnmodifiableIntShortMap(TIntShortMap m) {
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

    bool containsValue(short val) {
      return this.m.containsValue(val);
   }

    short get(int key) {
      return this.m.get(key);
   }

    short put(int key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short remove(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TIntShortMap m) {
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

    int getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    short getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TIntProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TShortProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TIntShortProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TIntShortIterator iterator() {
      return std::make_shared<1>(this);
   }

    short putIfAbsent(int key, short value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TShortFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TIntShortProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(int key, short amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    short adjustOrPutValue(int key, short adjust_amount, short put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
