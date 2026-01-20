#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/TCollections.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/impl/unmodifiable/TUnmodifiableIntByteMap/1.h"
#include "gnu/trove/iterator/TIntByteIterator.h"
#include "gnu/trove/map/TIntByteMap.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TIntByteProcedure.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/set/TIntSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableIntByteMap {
public:
    static const long serialVersionUID = -1034234728574286014L;
    const TIntByteMap m;
   private transient TIntSet keySet = nullptr;
   private transient TByteCollection values = nullptr;

    public TUnmodifiableIntByteMap(TIntByteMap m) {
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

    bool containsValue(uint8_t val) {
      return this.m.containsValue(val);
   }

    uint8_t get(int key) {
      return this.m.get(key);
   }

    uint8_t put(int key, uint8_t value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t remove(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void putAll(TIntByteMap m) {
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

    TByteCollection valueCollection() {
      if (this.values == nullptr) {
         this.values = TCollections.unmodifiableCollection(this.m.valueCollection());
      }

      return this.values;
   }

   public byte[] values() {
      return this.m.values();
   }

   public byte[] values(byte[] array) {
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

    uint8_t getNoEntryValue() {
      return this.m.getNoEntryValue();
   }

    bool forEachKey(TIntProcedure procedure) {
      return this.m.forEachKey(procedure);
   }

    bool forEachValue(TByteProcedure procedure) {
      return this.m.forEachValue(procedure);
   }

    bool forEachEntry(TIntByteProcedure procedure) {
      return this.m.forEachEntry(procedure);
   }

    TIntByteIterator iterator() {
      return std::make_shared<1>(this);
   }

    uint8_t putIfAbsent(int key, uint8_t value) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void transformValues(TByteFunction function) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool retainEntries(TIntByteProcedure procedure) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool increment(int key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool adjustValue(int key, uint8_t amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    uint8_t adjustOrPutValue(int key, uint8_t adjust_amount, uint8_t put_amount) {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
