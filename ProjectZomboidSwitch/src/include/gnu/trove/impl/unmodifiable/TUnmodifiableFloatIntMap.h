#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCollections.h"
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableFloatIntMap/1.h"
#include "gnu/trove/iterator/TFloatIntIterator.h"
#include "gnu/trove/map/TFloatIntMap.h"
#include "gnu/trove/procedure/TFloatIntProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TFloatSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableFloatIntMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TFloatIntMap m;
   private transient TFloatSet keySet = nullptr;
   private transient TIntCollection values = nullptr;

    public TUnmodifiableFloatIntMap(TFloatIntMap m) {
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

    bool containsValue(int val) {
      return this.m.containsValue(val);
   }

    int get(float key) {
      return this.m.get(key);
   }

    int put(float key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int remove(float key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TFloatIntMap m) {
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

    TIntCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public int[] values() {
      return this.m.values();
   }

   public int[] values(int[] array) {
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

    int getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TFloatProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TIntProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TFloatIntProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TFloatIntIterator iterator() {
      return std::make_shared<1>(this);
   }

    int putIfAbsent(float key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TIntFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TFloatIntProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(float key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(float key, int amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int adjustOrPutValue(float key, int adjust_amount, int put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
