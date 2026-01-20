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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableCharIntMap/1.h"
#include "gnu/trove/iterator/TCharIntIterator.h"
#include "gnu/trove/map/TCharIntMap.h"
#include "gnu/trove/procedure/TCharIntProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TCharSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharIntMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TCharIntMap m;
   private transient TCharSet keySet = nullptr;
   private transient TIntCollection values = nullptr;

    public TUnmodifiableCharIntMap(TCharIntMap m) {
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

    bool containsValue(int val) {
      return this.m.containsValue(val);
   }

    int get(char key) {
      return this.m.get(key);
   }

    int put(char key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int remove(char key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TCharIntMap m) {
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

    char getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    int getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TCharProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TIntProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TCharIntProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TCharIntIterator iterator() {
      return std::make_shared<1>(this);
   }

    int putIfAbsent(char key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TIntFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TCharIntProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(char key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(char key, int amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int adjustOrPutValue(char key, int adjust_amount, int put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
