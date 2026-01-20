#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntCharMap/1.h"
#include "gnu/trove/iterator/TIntCharIterator.h"
#include "gnu/trove/map/TIntCharMap.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TIntCharProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntCharMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TIntCharMap m;
   private transient TIntSet keySet = nullptr;
   private transient TCharCollection values = nullptr;

    public TUnmodifiableIntCharMap(TIntCharMap m) {
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

    bool containsValue(char val) {
      return this.m.containsValue(val);
   }

    char get(int key) {
      return this.m.get(key);
   }

    char put(int key, char value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char remove(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TIntCharMap m) {
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

    TCharCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public char[] values() {
      return this.m.values();
   }

   public char[] values(char[] array) {
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

    char getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TIntProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TCharProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TIntCharProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TIntCharIterator iterator() {
      return std::make_shared<1>(this);
   }

    char putIfAbsent(int key, char value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TCharFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TIntCharProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(int key, char amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    char adjustOrPutValue(int key, char adjust_amount, char put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
