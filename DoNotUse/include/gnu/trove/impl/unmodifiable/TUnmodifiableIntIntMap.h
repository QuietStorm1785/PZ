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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntIntMap/1.h"
#include "gnu/trove/iterator/TIntIntIterator.h"
#include "gnu/trove/map/TIntIntMap.h"
#include "gnu/trove/procedure/TIntIntProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntIntMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TIntIntMap m;
   private transient TIntSet keySet = nullptr;
   private transient TIntCollection values = nullptr;

    public TUnmodifiableIntIntMap(TIntIntMap m) {
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

    bool containsValue(int val) {
      return this.m.containsValue(val);
   }

    int get(int key) {
      return this.m.get(key);
   }

    int put(int key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int remove(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TIntIntMap m) {
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

    int getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    int getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TIntProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TIntProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TIntIntProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TIntIntIterator iterator() {
      return std::make_shared<1>(this);
   }

    int putIfAbsent(int key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TIntFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TIntIntProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(int key, int amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int adjustOrPutValue(int key, int adjust_amount, int put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
