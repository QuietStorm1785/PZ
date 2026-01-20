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
#include "gnu/trove/impl/unmodifiable/TUnmodifiableByteIntMap/1.h"
#include "gnu/trove/iterator/TByteIntIterator.h"
#include "gnu/trove/map/TByteIntMap.h"
#include "gnu/trove/procedure/TByteIntProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TByteSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableByteIntMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TByteIntMap m;
   private transient TByteSet keySet = nullptr;
   private transient TIntCollection values = nullptr;

    public TUnmodifiableByteIntMap(TByteIntMap m) {
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

    bool containsKey(uint8_t key) {
      return this.m.containsKey(key);
   }

    bool containsValue(int val) {
      return this.m.containsValue(val);
   }

    int get(uint8_t key) {
      return this.m.get(key);
   }

    int put(uint8_t key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int remove(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TByteIntMap m) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(Map<? extends, ? extends) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    TByteSet keySet() {
      if (this.keySet == nullptr) {
         this.keySet = TCollections.unmodifiableSet(this.m.keySet());
      }

      return this.keySet;
   }

   public byte[] keys() {
      return this.m.keys();
   }

   public byte[] keys(byte[] array) {
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

    uint8_t getNoEntryKey() {
      return this.m.getNoEntryKey();
   }

    int getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TByteProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TIntProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TByteIntProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TByteIntIterator iterator() {
      return std::make_shared<1>(this);
   }

    int putIfAbsent(uint8_t key, int value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TIntFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TByteIntProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(uint8_t key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(uint8_t key, int amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int adjustOrPutValue(uint8_t key, int adjust_amount, int put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
